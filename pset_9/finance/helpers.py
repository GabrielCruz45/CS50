import requests
import sys

from datetime import datetime
from cs50 import SQL
from flask import redirect, render_template, session
from functools import wraps

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

# history logging function
def addHistory(mode, username, userId, stockSymbol, quantityOfShares, stockPrice):
    # create userHistory table (if not exists); using try-except because gemini said so
    tableName = username + "_" + str(userId) + "_history"

    try:
        db.execute(f"CREATE TABLE IF NOT EXISTS {tableName} (stock_symbol TEXT NOT NULL, shares_quantity NUMERIC NOT NULL, share_price NUMERIC NOT NULL, time_and_date TEXT NOT NULL)")

    except Exception as e:
        print(f"Error creating table: {e}")
        return apology("Error creating table.")

    # get current date and time
    timeAndDate = str(datetime.now())
    timeAndDate = timeAndDate[:19]

    if mode == "purchase":
        shareSign = 1
    elif mode == "sale":
        shareSign = -1
    else:
        print("Error with addHistory 'mode' value.")
        return sys.exit(1)

    # update user history table
    history = db.execute(f"INSERT INTO {tableName} (stock_symbol, shares_quantity, share_price, time_and_date) VALUES (?, ?, ?, ?)", stockSymbol.upper(), (quantityOfShares * shareSign), stockPrice, str(timeAndDate))

    return history
