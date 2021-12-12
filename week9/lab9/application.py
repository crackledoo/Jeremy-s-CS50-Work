import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        #verify the submitted data fields:
        name = request.form.get("name")
        if not name:
            return render_template("error.html", message="Missing name")
        month = request.form.get("month")
        if not month or int(month) > 12 or int(month) < 0:
            return render_template("error.html", message="Missing month")
        day = request.form.get("day")
        if not day or int(day) > 31 or int(day) < 0:
            return render_template("error.html", message="Missing day")
        #add the user's birthday to the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        #dsisplay the entries in the database on index.html
        persons = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", persons=persons)


