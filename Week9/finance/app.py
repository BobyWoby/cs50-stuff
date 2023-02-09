import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import datetime
from werkzeug.security import check_password_hash, generate_password_hash
import math
import re

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #CREATE TABLE bought_stocks(account_id TEXT NOT NULL, symbol TEXT NOT NULL, price NUMERIC NOT NULL, shares NUMBERIC NOT NULL, total_value NUMBER NOT NULL, FOREIGN KEY(account_id) REFERENCES users(id));
    stocks = db.execute("SELECT * FROM bought_stocks WHERE account_id = ?", session['user_id'])
    holdings_val = 0
    for stock in stocks:
        db.execute("UPDATE bought_stocks SET price = ?, total_value = ? WHERE symbol = ?", lookup(stock['symbol'])['price'], lookup(stock['symbol'])['price'] * stock['shares'], stock['symbol'])
        holdings_val += stock['total_value']
    stocks = db.execute("SELECT * FROM bought_stocks WHERE account_id = ?", session['user_id'])
    for stock in stocks:
        stock['price'] = usd(stock['price'])
        stock['total_value'] = usd(stock['total_value'])
    userInfo = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])
    bal = usd(userInfo[0]['cash'])
    total_val = usd(userInfo[0]['cash'] + holdings_val)
    return render_template("index.html", stocks=stocks, bal=bal, total_val=total_val)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #DONT FORGET TO MAKE A SQL TABLE CALLED purchase_log
    #CREATE TABLE purchase_log(account_id TEXT NOT NULL, symbol TEXT NOT NULL,
    #price NUMERIC NOT NULL, hours INTEGER, minutes INTEGER, seconds INTEGER,
    # FOREIGN KEY(account_id) REFERENCES users(id))
    if request.method == "POST":
        #return apology("Somtehings not working")
        symbol = request.form.get("symbol")
        if not lookup(symbol):
            return apology("NOPE", 400)
            flash("Enter a proper symbol")
            return render_template("sell.html")
        stockPrice = lookup(symbol)['price']
        stockName = lookup(symbol)['name']
        shares = request.form.get("shares")
        if not shares:
            return apology("NOPE", 400)
        if not shares.isnumeric():
            return apology("NOPE",400)
        shares = int(shares)
        totalCost = float(stockPrice) * shares
        if shares <= 0:
            return render_template("buy.html")
        userBal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        #You need to add logic to check to make sure the person has enough money

        if float(userBal) < totalCost:
             return apology("ur too broke", 503)
        db.execute("INSERT INTO logs (account_id, action, symbol, price, shares) VALUES (?, 'buy', ?, ?, ?)", session["user_id"], symbol, stockPrice, shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(userBal)-totalCost, session["user_id"])
        #if the user has bought the stock before
        if db.execute("SELECT COUNT(*) FROM bought_stocks WHERE symbol LIKE ? AND account_id = ?", symbol, session["user_id"])[0]['COUNT(*)'] > 0:
            stockShares = db.execute("SELECT shares FROM bought_stocks WHERE symbol LIKE ? AND account_id = ?", symbol, session["user_id"])[0]['shares']
            db.execute("UPDATE bought_stocks SET shares = ?, price = ?, total_value = ? WHERE account_id = ? AND symbol = ?", stockShares + shares, lookup(symbol)['price'], lookup(symbol)['price'] * (stockShares + shares), session["user_id"], symbol)
        #otherwise do thing
        else:
            db.execute("INSERT INTO bought_stocks (account_id, symbol, price, shares, total_value) VALUES (?, ?, ?, ?, ?)", session['user_id'], symbol, lookup(symbol)['price'],shares, lookup(symbol)['price'] * shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userBal - totalCost, session['user_id'])
        return redirect("/")

    elif request.method == "GET":
        return render_template("buy.html")
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    #CREATE TABLE logs(account_id TEXT NOT NULL, action TEXT NOT NULL, symbol TEXT NOT NULL, price NUMERIC NOT NULL, shares NUMBERIC NOT NULL, year INTEGER, month INTEGER, day INTEGER, hour INTEGER, minute INTEGER, second INTEGER, FOREIGN KEY(account_id) REFERENCES users(id));
    logs = db.execute("SELECT * FROM logs WHERE account_id = ?", session['user_id'])
    return render_template("history.html", logs=logs)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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
    """Get stock quote."""
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("NOPE", 400)
        symbol["price"] = usd(symbol["price"])
        return render_template("quoted.html", symbol=symbol)
    elif request.method == "GET":
        return render_template("quote.html")
    return redirect("/")

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Get stock quote."""
    if request.method == "POST":
        amount = float(request.form.get("amount"))
        if amount <= 0:
            flash("Enter a valid amount of money")
            return apology("NOPE", 400)
            return render_template("deposit.html")
        current_amount = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        db.execute("UPDATE users SET cash = ? WHERE id = ?", amount + current_amount, session['user_id'])
        return redirect("/")
    elif request.method == "GET":
        return render_template("deposit.html")
    return redirect("/")

@app.route("/withdraw", methods=["GET", "POST"])
@login_required
def withdraw():
    """Get stock quote."""
    if request.method == "POST":
        amount = float(request.form.get("amount"))
        if amount <= 0:
            flash("Enter a valid amount of money")
            return apology("NOPE", 400)
            return render_template("withdraw.html")
        current_amount = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        if current_amount < amount:
            flash("Ur too broke for that, idiot")
            return apology("NOPE", 400)
            return render_template("withdraw.html")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", amount + current_amount, session['user_id'])
        return redirect("/")
    elif request.method == "GET":
        return render_template("withdraw.html")
    return redirect("/")

@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Get stock quote."""
    return render_template("account.html")

@app.route("/sellall", methods=["GET", "POST"])
def sellall():
    """Sell all stocks"""

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            flash("Enter a proper username")
            return apology("NOPE", 400)
            return render_template("register.html")
        if not request.form.get("password"):
            flash("Enter a proper password")
            return apology("NOPE", 400)
            return render_template("register.html")
        if not request.form.get("confirmation"):
            flash("Confirm the password")
            return apology("NOPE", 400)
            return render_template("register.html")
        confirmation = request.form.get("confirmation")
        username = request.form.get("username")
        password = request.form.get("password")
        if re.search("\W", password) == None and re.search("\D", password) != None:
            flash("Please input a special character")
            return apology("NOPE", 400)
            return render_template("register.html")
        if not password == confirmation:
            flash("The passwords don't match")
            return apology("NOPE", 400)
            return render_template("register.html")
        hashed = generate_password_hash(password)
        if db.execute("SELECT COUNT(*) FROM users WHERE username LIKE ?", username)[0]["COUNT(*)"] >= 1:
            flash("That username is taken")
            return apology("NOPE", 400)
            return render_template("register.html")


        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",username,hashed)
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/change_password", methods=["GET", "POST"])
def change_password():
    """Change the users password"""
    if request.method == "POST":
        if not request.form.get("password1"):
            flash("Enter a password")
            return apology("NOPE", 400)
            return render_template("passsword_change.html")
        if not request.form.get("password"):
            flash("Enter a proper symbol")
            return apology("NOPE", 400)
            return render_template("passsword_change.html")
        if not request.form.get("password") == request.form.get("password1"):
            flash("The passwords don't match up")
        if re.search("\W", password) == None and re.search("\D", password) != None:
            flash("Please input a special character")
            return apology("NOPE", 400)
            render_template("change_password.html")
        password = request.form.get("password")
        password = generate_password_hash(password)
        db.execute("UPDATE users (hash) VALUES(?) WHERE id = ?",password, hash(session['user_id']))
        return redirect("/")
    else:
        return render_template("change_password.html")

@app.route("/change_username", methods=["GET", "POST"])
def change_username():
    """Change the users password"""
    if request.method == "POST":
        if not request.form.get("password1"):
            flash("Enter a password")
            return apology("NOPE", 400)
            return render_template("passsword_change.html")
        if not request.form.get("password"):
            flash("Enter a proper symbol")
            return apology("NOPE", 400)
            return render_template("passsword_change.html")
        if not request.form.get("password") == request.form.get("password1"):
            flash("The passwords don't match up")
            return apology("NOPE", 400)
            return render_template("password_change.html")
        password = request.form.get("password")
        password = generate_password_hash(password)
        db.execute("UPDATE users (hash) VALUES(?) WHERE id = ?",password, hash(session['user_id']))
        return redirect("/")
    else:
        return render_template("change_username.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
     #CREATE TABLE sell_log(account_id TEXT NOT NULL, symbol TEXT NOT NULL, price NUMERIC NOT NULL, hours INTEGER, minutes INTEGER, seconds INTEGER, FOREIGN KEY(account_id) REFERENCES users(id));
    if request.method == "POST":

        userBal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        symbol = request.form.get("symbol")
        if not lookup(symbol):
            flash("Enter a valid symbol")
            return render_template("sell.html")
        stockPrice = lookup(symbol)['price']
        stockName = lookup(symbol)['name']
        shares = int(request.form.get("shares"))
        totalCost = float(stockPrice) * shares
        if db.execute("SELECT COUNT(*) FROM bought_stocks WHERE symbol LIKE ? AND account_id = ?", symbol, session["user_id"])[0]['COUNT(*)'] <= 0:
            return apology("you dont own that stock, you moron")
        ownedShares = db.execute("SELECT shares FROM bought_stocks WHERE symbol LIKE ? AND account_id = ?", symbol, session["user_id"])[0]['shares']

        if shares > ownedShares:
            return apology("ur actually incapable of counting, aren't you")

        db.execute("UPDATE bought_stocks SET shares = ? WHERE account_id = ? AND symbol = ?", ownedShares - shares, session['user_id'], symbol)
        if db.execute("SELECT shares FROM bought_stocks WHERE symbol LIKE ? AND account_id = ?", symbol, session["user_id"])[0]['shares'] <= 0:
            db.execute("DELETE FROM bought_stocks WHERE symbol = ?", symbol)
        db.execute("INSERT INTO logs (account_id, action, symbol, price, shares) VALUES (?, 'sell', ?, ?, ?)", session["user_id"], symbol, stockPrice, shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userBal + totalCost, session['user_id'])
        return redirect("/")
    elif request.method == "GET":
        stocks = db.execute("SELECT * FROM bought_stocks WHERE account_id = ?", session["user_id"])
        return render_template("sell.html", stocks=stocks)
    return apology("TODO")
