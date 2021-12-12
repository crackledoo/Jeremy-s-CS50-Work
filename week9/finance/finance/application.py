import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    portfolio_db_extract = db.execute("SELECT stockname, stockqty FROM portfolios WHERE userid = ?", session["user_id"])
    portfolio = []
    walletprice = 0
    for x in portfolio_db_extract:
        #initialize variables
        stock = {}
        stock['name'] = x.get('stockname')
        stock['qty'] = x.get('stockqty')
        money = int(lookup(x.get('stockname')).get('price'))
        stock['price'] = usd(money)
        walletprice = int(walletprice) + money

        #add to portfolio
        portfolio.append(stock)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0].get('cash')
    cash = usd(cash)
    walletprice = usd(walletprice)
    return render_template("index.html", portfolio = portfolio, walletprice = walletprice, cash = cash)
    #stockname=stockname, stockqty=stockqty, stockprice=usd(stockprice))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    #FIRST TEMPLATE FOR BUYING
    if request.method == "GET":
        if not request.args.get("stock"):
            return apology("No stock submitted with your HTTP request", 400)
        stock = request.args.get("stock")
        stockInfo = lookup(stock)
        quotedPrice = stockInfo.get('price')
        quotedName = stockInfo.get('name')
        return render_template("buy.html", stock=stock, quotedName=quotedName, quotedPrice=quotedPrice)

    #TEMPLATE FOR HAVING BOUGHT
    if request.method == "POST":
        #INITIALIZING VARIABLES
        availableFunds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        availableFunds = availableFunds[0].get('cash')
        stock = request.form.get("stock")
        whetherStockname = db.execute("SELECT stockname FROM portfolios WHERE userid = ? AND stockname = ?", session["user_id"], stock)
        if not whetherStockname:
            #whetherUsername = db.execute("SELECT userid FROM portfolios WHERE userid = ?", session["user_id"])
            #if not whetherUsername:
            db.execute("INSERT INTO portfolios (stockname, userid) VALUES (?, ?)", stock, session["user_id"])
            #else:
                #db.execute("INSERT INTO portfolios (stockname) VALUES (?) WHERE userid = ?", stock, session["user_id"])
        qtyBefore = db.execute("SELECT stockqty FROM portfolios WHERE userid = ? AND stockname = ?", session["user_id"], stock)
        if not qtyBefore:
            qtyBefore = [{'stockqty':0}]
        if len(qtyBefore) > 1:
            return apology("Awful database error. Sorry.")
        qty = request.form.get("qty")
        if not qty:
            return apology("Failed to find purchasable quantity")
        qty = int(qty)
        if qty > 2000 or qty < 1:
            return apology("Failed to find purchasable quantity")
        stockInfo = lookup(stock)
        if not stockInfo:
            return apology("Failed to find selected stock")
        price = stockInfo.get('price')
        price = int(qty) * price
        remainingBalance = availableFunds - price
        if remainingBalance < 0:
            return apology("Insufficient funds")
        qtyNew = qtyBefore[0].get('stockqty') + int(qty)

        #BEGIN TRANSACTION
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingBalance, session["user_id"])
        db.execute("UPDATE portfolios SET stockqty = ? WHERE userid = ? AND stockname = ?", qtyNew, session["user_id"], stock)
        brandNewQtyForDebugging = db.execute("SELECT stockqty FROM portfolios WHERE stockname = ? AND userid = ?", stock, session["user_id"])
        print("AND THE NEWEST QTY ISSSS::")
        print(brandNewQtyForDebugging)

        #RECORD TRANSACTION IN HISTORY
        db.execute("INSERT INTO histories(type, datetime, symbol, qty, totalPrice, userid) VALUES ('buy', datetime('now'), ?, ?, ?, ?)", stock, qty, price, session["user_id"])
        return render_template("bought.html", stock=stock, qty=qty)



@app.route("/history")
@login_required
def history():
    history_db_extract = db.execute("SELECT * FROM histories WHERE userid = ? ORDER BY datetime DESC", session["user_id"])
    history = []
    for x in history_db_extract:
        #initialize variables
        stock = {}
        stock['name'] = x.get('symbol')
        stock['qty'] = x.get('qty')
        stock['type'] = x.get('type')
        stock['datetime'] = x.get('datetime')
        money = lookup(stock['name'])
        money = int(money.get('price'))
        stock['price'] = usd(money)
        #make plus and minus
        if 'buy' in stock['type']:
            stock['price'] = '-' + stock['price']
        else:
            stock['price'] = '+' + stock['price']
        #add to portfolio
        history.append(stock)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0].get('cash')
    cash = usd(cash)
    return render_template("history.html", history = history, cash = cash)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote")
@login_required
def quote():
    return render_template("quote.html")


@app.route("/quoted")
@login_required
def quoted():
    symbol = request.args.get("symbol")
    stocks = lookup(symbol)
    return stocks


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password and confirmation", 400)
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password not in confirmation:
            return apology("Confirmation does not match password")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("That username is already taken", 400)
        password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password)
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    #FIRST TEMPLATE FOR SELLING
    if request.method == "GET":
        stock = request.args.get("stock")
        stockInfo = lookup(str(stock))
        quotedPrice = stockInfo.get('price')
        quotedName = stockInfo.get('name')
        return render_template("sell.html", stock=stock, quotedName=quotedName, quotedPrice=usd(quotedPrice))


    #TEMPLATE FOR HAVING SOLD
    if request.method == "POST":
        #INITIALIZING VARIABLES
        availableFunds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        availableFunds = availableFunds[0].get('cash')
        stock = request.form.get("stock")
        whetherStockname = db.execute("SELECT stockname FROM portfolios WHERE userid = ? AND stockname = ?", session["user_id"], stock)
        if not whetherStockname:
            return apology("Ah! This portfolio doesn't seem to exist in our transaction records! Please reach out to customer support at 123-456-7890")
        qtyBefore = db.execute("SELECT stockqty FROM portfolios WHERE userid = ? AND stockname = ?", session["user_id"], stock)
        if not qtyBefore:
            return apology("Failed to find your shares! Please reach out to customer support at 123-456-7890")
        if len(qtyBefore) > 1:
            return apology("Awful database error. Sorry.")
        qty = request.form.get("qty")
        if not qty:
            return apology("Failed to find sellable quantity")
        qty = int(qty)
        if qty > 2000 or qty < 1:
            return apology("Failed to find sellable quantity")
        stockInfo = lookup(stock)
        if not stockInfo:
            return apology("Failed to find selected stock")
        price = stockInfo.get('price')
        price = int(qty) * price
        newBalance = availableFunds + price
        if newBalance < 0:
            return apology("Math error!")
        qtyNew = qtyBefore[0].get('stockqty') - int(qty)

        #DEBUGGING STUFF HERE
        print("Available Funds:")
        print(availableFunds)
        print("stock is:")
        print(stock)
        print("qtyBefore is:")
        print(qtyBefore)
        print("qty is:")
        print(qty)
        print("stockInfo is:")
        print(stockInfo)
        print("qtyNew is:")
        print(qtyNew)
        print("The price is:")
        print(price)
        print("newBalance is:")
        print(newBalance)

        #BEGIN TRANSACTION
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"])
        db.execute("UPDATE portfolios SET stockqty = ? WHERE userid = ? AND stockname = ?", qtyNew, session["user_id"], stock)
        brandNewQtyForDebugging = db.execute("SELECT stockqty FROM portfolios WHERE stockname = ? AND userid = ?", stock, session["user_id"])
        print("AND THE NEWEST QTY ISSSS::")
        print(brandNewQtyForDebugging)

        #RECORD TRANSACTION IN HISTORY
        db.execute("INSERT INTO histories(type, datetime, symbol, qty, totalPrice, userid) VALUES ('sell', datetime('now'), ?, ?, ?, ?)", stock, qty, price, session["user_id"])
        return render_template("sold.html", stock=stock, qty=qty, price=usd(price))


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)