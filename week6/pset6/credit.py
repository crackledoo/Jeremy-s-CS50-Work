import cs50

def main():
    number = get_number()
    if validate(number) is False:
        print("INVALID")
    else:
        carrier = identify(number)
        print (carrier)

def get_number():
    #receive card number from recipient
    while(True):
        number = input("Number: ")
        #require numeric input
        if number.isnumeric():
            break
    return number

def validate(number):
    #Validate length of card input
    sum = 0
    if len(number) == 13 or 15 or 16:
    #Validate credit card number with Luhn's algorithm
        for i in range(2, len(number) + 1, 2):
            digit = int(number[len(number) - i])
            digit *= 2
            if digit >= 10:
                sum += (digit % 10)
                sum += 1
            else:
                sum += digit
        for i in range(1, len(number)+ 1, 2):
            digit = int(number[len(number) - i])
            sum += (digit)
        #print(f"final sum is {sum}")
        if sum % 10 == 0:
            return True
    return False

def identify(number):
    #Identify carrier as either AMEX, MASTERCARD or VISA
    carrier = 'INVALID'
    #print(len(number))
    if len(number) == 16:
        #look for MASTERCARD or VISA
        if int(number[0]) == 4:
            carrier = 'VISA'
        elif int(number[0]) == 5:
            if int(number[1]) == 1 or 2 or 3 or 4 or 5:
                carrier = 'MASTERCARD'
    elif len(number) == 15:
        #look for AMEX
        if int(number[0]) == 3:
            if int(number[1]) == 4 or 7:
                carrier = 'AMEX'
    elif len(number) == 13:
        #look for VISA again
        if int(number[0]) == 4:
            carrier = 'VISA'

    return carrier

main()