import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import re

from helpers import apology, login_required, lookup, usd, addHistory

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/changePassword", methods=["GET", "POST"])
@login_required
def changePassword():

    if request.method == 'POST':
        userId = session.get("user_id")
        if not userId:
            apology("Invalid user.")

        newPassword = request.form.get("newPassword")
        if not newPassword or type(newPassword) is not str:
            apology("Must write valid password")

        newPasswordConfirmation = request.form.get("newPasswordConfirmation")
        if not newPasswordConfirmation or type(newPasswordConfirmation) is not str:
            apology("Must write valid password confirmation")

        if newPassword != newPasswordConfirmation:
            apology("Password and password confirmation must match")

        passwordHashed = generate_password_hash(newPassword)

        if not (db.execute("UPDATE users SET hash = ? WHERE id = ?", passwordHashed, userId)):
            return apology("Password could not be changed.")

        return redirect("/")

    return render_template("changePassword.html")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # 'seed' variables
    userId = session.get("user_id")
    if not userId:
        return redirect("/login")

    username = (db.execute("SELECT username FROM users WHERE id = ?", userId))[0]['username']

    # check if username not None and logged in
    if not username:
        return redirect("/register")

    # create table name
    tableName = username + "_" + str(userId) + "_portfolio"

    # create user->stock table (if not exists); using try-except because gemini said so
    try:
        db.execute(
            f"CREATE TABLE IF NOT EXISTS {tableName} (stock_symbol TEXT NOT NULL, shares_quantity NUMERIC NOT NULL)")

    except Exception as e:
        print(f"Error creating table: {e}")
        return apology("Error creating table.")

    # look up cash on hand
    cashOnHand = (db.execute("SELECT cash FROM users WHERE id = ?", userId))[0]['cash']

    # can return 0 stockSymbols, 1 stockSymbols or 2+ stockSymbols
    stockSymbol = db.execute(f"SELECT stock_symbol FROM {tableName}")

   # initialize list of dictionary w/tuples as values for user portfolio
    userPortfolio = []

    totalSum = cashOnHand

    # populate user portfolio
    for stocks in stockSymbol:
        for value in stocks.values():
            sharesQuantity = int((db.execute(
                f"SELECT shares_quantity FROM {tableName} WHERE stock_symbol = ?", value))[0]['shares_quantity'])
            sharesValue = float((lookup(value))['price'])
            userPortfolio.append(
                {value: (sharesQuantity, sharesValue, (sharesQuantity * sharesValue))})
        totalSum = totalSum + (sharesValue * sharesQuantity)

    return render_template("index.html", userPortfolio=userPortfolio, cashOnHand=cashOnHand, username=username, totalSum=totalSum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':

        # get user input
        stockSymbol = (request.form.get("symbol")).upper()
        quantityOfShares = request.form.get("shares")

        # look up stock info
        stockInfo = lookup(stockSymbol)

        # check if valid stock name
        if not stockInfo:
            # if invalid, apology time
            return apology("Must enter a valid stock symbol.")

        # quantityOfShares check
        if not quantityOfShares.isnumeric():
            return apology("Stock quantity must be positive integer.")

        quantityOfShares = int(quantityOfShares)

        if not quantityOfShares > 0:
            return apology("Stock quantity must be positive integer.")

        # variables for user table
        userId = session.get("user_id")
        username = (db.execute("SELECT username FROM users WHERE id = ?", userId))[0]['username']
        tableName = username + "_" + str(userId) + "_portfolio"

        # check for user portfolio, create user->stock table (if not exists)
        try:
            db.execute(
                f"CREATE TABLE IF NOT EXISTS {tableName} (stock_symbol TEXT NOT NULL, shares_quantity NUMERIC NOT NULL)")

        except Exception as e:
            print(f"Error creating table: {e}")
            return apology("Error creating table.")

        # look for how much cash user has, convert to float from str
        # (it is not converted to int because it truncates the total)
        cashoOnHand = float(
            (db.execute("SELECT cash FROM users WHERE username = ?", username))[0]['cash'])

        # look for stock price,
        stockPrice = stockInfo['price']

        # multiply single stock price times user quantity
        purchasePrice = stockPrice * quantityOfShares

        # check if user has $$$
        if cashoOnHand < purchasePrice:
            return apology("You don't have enough cash on hand.")

        # update databases AKA: IT'S MIGHTY BUYING TIME
        # check if stock_symbol already present in user's portfolio
        if not db.execute(f"SELECT stock_symbol FROM {tableName} WHERE stock_symbol = ?", stockSymbol):
            # if not, insert stock_symbol to users portfolio
            db.execute(
                f"INSERT INTO {tableName} (stock_symbol, shares_quantity) VALUES (?, ?)", stockSymbol, quantityOfShares)

            # update cash values on users' table
            previousCashQuantity = float(
                (db.execute("SELECT cash FROM users WHERE id = (?)", int(userId)))[0]['cash'])

            # UPDATE (user portfolio) TIME BBY
            db.execute(
                f"UPDATE {tableName} SET shares_quantity = (?) WHERE stock_symbol = (?)", quantityOfShares, stockSymbol)

            # bye bye buy money :( lol rawr xD
            db.execute("UPDATE users SET cash = (?) WHERE id = (?)",
                       (float(previousCashQuantity) - float(purchasePrice)), int(userId))

            # add transaction to history
            addHistory('purchase', username, userId, stockSymbol, quantityOfShares, stockPrice)
            return redirect("/")

        else:
            # if does exists:
            # get previous numbers of shares, and convert from list of dicts to int
            previousSharesQuantity = int((db.execute(
                f"SELECT shares_quantity FROM {tableName} WHERE stock_symbol = (?)", stockSymbol))[0]['shares_quantity'])

            # same thing with cash values
            previousCashQuantity = float(
                (db.execute("SELECT cash FROM users WHERE id = (?)", int(userId)))[0]['cash'])

            # UPDATE (user portfolio) TIME BBY
            db.execute(f"UPDATE {tableName} SET shares_quantity = (?) WHERE stock_symbol = (?)",
                       (quantityOfShares + previousSharesQuantity), stockSymbol)

            # bye bye buy money
            db.execute("UPDATE users SET cash = ? WHERE id = ?", (float(
                       previousCashQuantity) - float(purchasePrice)), int(userId))

            # add transaction to history table
            addHistory('purchase', username, userId, stockSymbol, quantityOfShares, stockPrice)

            return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # check if user has table
    userId = session.get("user_id")
    username = (db.execute("SELECT username FROM users WHERE id = ?", userId))[0]['username']

    # create table name
    tableName = username + "_" + str(userId) + "_history"

    # create a history table if it does not exist
    try:
        db.execute(
            f"CREATE TABLE IF NOT EXISTS {tableName} (stock_symbol TEXT NOT NULL, shares_quantity NUMERIC NOT NULL, share_price NUMERIC NOT NULL, time_and_date TEXT NOT NULL)")

    except Exception as e:
        print(f"Error creating table: {e}")
        return apology("Error creating table.")

    userHistory = db.execute(f"SELECT * FROM {tableName}")

    return render_template("history.html", userHistory=userHistory)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Quote User's Input Symbol"""

    if request.method == 'POST':
        # user input on html file
        stock = (request.form.get("symbol")).upper()

        # look for info, if not valid will output None
        stockLookup = lookup(stock)

        # check if valid stock name
        if not stockLookup:
            # if invalid, apology time
            return apology("Must enter a valid stock symbol.")

        # stockLookup['price'] = usd(stockLookup['price'])

        # render same html file with searched stock information
        return render_template("quote.html", stockLookup=stockLookup)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        # get data from html page
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # validate user input
        if not username:
            return apology("Must provide username", 400)
        if not password:
            return apology("Must provide password", 400)
        if not confirmation or password != confirmation:
            return apology("Passwords must match.", 400)

        # sanitize username because gemini said so; idk man
        username = re.sub(r'[^a-zA-Z0-9_]', '', username)

        # check if in database
        if db.execute("SELECT 1 FROM users WHERE username = ? LIMIT 1", username):
            return apology("Username already exists", 400)

        # hash password
        passwordHashed = generate_password_hash(password)

        # add to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, passwordHashed)

        # login user automatically
        login = (db.execute("SELECT id FROM users WHERE username = ?", username))[0]["id"]
        session["user_id"] = login

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == 'POST':
        # get user input
        stockSymbol = (request.form.get("symbol")).upper()
        quantityOfShares = request.form.get("shares")

        if not stockSymbol:
            return apology("Must choose a stock symbol.")

        # change quantityOfShares from text to int
        quantityOfShares = int(quantityOfShares)

        # look up stock info and store it
        stockInfo = lookup(stockSymbol)

        # validate user input
        if not stockInfo or not quantityOfShares > 0:
            # apology time
            return apology("Invalid Stock symbol or quantity of stocks.")

        # check if user has table
        userId = str(session.get("user_id"))
        username = str(
            (db.execute("SELECT username FROM users WHERE id = ?", userId))[0]['username'])
        tableName = username + "_" + str(userId) + "_portfolio"

        if not db.execute(f"SELECT * FROM {tableName}"):
            return apology("You don't have any stocks.")

        # look for stock price
        stockPrice = stockInfo['price']

        # multiply single stock price times user quantity
        sellingPrice = stockPrice * int(quantityOfShares)

        # update databases AKA: IT'S MIGHTY SELLING TIME
        # check if stock_symbol already present in user's portfolio
        if not db.execute(f"SELECT stock_symbol FROM {tableName} WHERE stock_symbol = ?", stockSymbol):
            # if not, apology
            return apology("You don't have those stocks")

        # if does exists:
        # get previous numbers of shares, and convert from list of dicts to int
        previousSharesQuantity = int((db.execute(
            f"SELECT shares_quantity FROM {tableName} WHERE stock_symbol = (?)", stockSymbol))[0]['shares_quantity'])

        # check if user has enough shares to sell
        if previousSharesQuantity < quantityOfShares:
            return apology("You don't have that quantity of shares to sell.")

        # same thing with cash values
        previousCashQuantity = float(
            (db.execute("SELECT cash FROM users WHERE id = (?)", int(userId)))[0]['cash'])

        # UPDATE (user portfolio) TIME BBY
        # delete sql row if stocks are now 0
        if (previousSharesQuantity - quantityOfShares) == 0:
            db.execute(f"DELETE FROM {tableName} WHERE stock_symbol = ?", stockSymbol)
        else:
            db.execute(f"UPDATE {tableName} SET shares_quantity = (?) WHERE stock_symbol = (?)",
                       (previousSharesQuantity - quantityOfShares), stockSymbol)

        # hello buy money :) lol rawr xdddd
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (float(
            previousCashQuantity) + float(sellingPrice)), int(userId))

        # add transaction to history table
        addHistory('sale', username, userId, stockSymbol, quantityOfShares, stockPrice)

        return redirect("/")

    else:
        # check if user has table
        userId = session.get("user_id")
        username = (db.execute("SELECT username FROM users WHERE id = ?", userId))[0]['username']

        # create table name
        tableName = username + "_" + str(userId) + "_portfolio"

        if not db.execute(f"SELECT * FROM {tableName}"):
            return apology("You have not made any transactions.")

        stockSymbols = db.execute(f"SELECT stock_symbol FROM {tableName}")

        for i in range(len(stockSymbols)):
            stockSymbols[i] = (stockSymbols[i]['stock_symbol']).upper()

        return render_template("sell.html", stockSymbols=stockSymbols)
