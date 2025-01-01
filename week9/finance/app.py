from  cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total = cash
    for stock in stocks:
        stock["price"] = lookup(stock["symbol"])["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        total += stock["total"]
    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not name:
            return apology("must provide username", 400)
        if db.execute("SELECT * FROM users WHERE username = ?", name):
            return apology("username already exists", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide confirmation", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)
        else:
            hash = generate_password_hash(password)
            if db.execute("SELECT * FROM users WHERE username = ?", name):
                return apology("username already exists", 400)
            # Insert the new user
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, hash)
            return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/reset", methods=["GET", "POST"])
def reset():
    """Reset password"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide confirmation", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)
        else:
            if not db.execute("SELECT * FROM users WHERE username = ?", username):
                return apology("username does not exist", 400)
            hash = generate_password_hash(password)
            db.execute("UPDATE users SET hash = ? WHERE username = ?", hash, username)
            return redirect("/login")
    else:
        return render_template("reset.html")


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
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])
    else:
        return render_template("quote.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        if not shares.isdigit():
            return apology("must provide shares", 400)
        if int(shares) < 1:
            return apology("must provide shares", 400)

        user_id = session["user_id"]
        # Check if user owns enough shares
        owned_shares = db.execute("SELECT SUM(shares) as total FROM transactions WHERE user_id = ? AND symbol = ?",
                                  user_id, symbol)[0]["total"]

        if owned_shares is None or owned_shares < int(shares):
            return apology("too many shares", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        cash = user[0]["cash"]
        price = stock["price"]
        total = price * int(shares)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + total, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, stock["symbol"], -int(shares), price)
        return redirect("/")
    else:
        user_id = session["user_id"]
        stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    ''' Buy shares of stock '''
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        if not shares.isdigit():
            return apology("must provide shares", 400)
        if int(shares) < 1:
            return apology("must provide shares", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        cash = user[0]["cash"]
        price = stock["price"]
        total = price * int(shares)
        if cash < total:
            return apology("can't afford", 400)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, price)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


if __name__ == "__main__":
    app.run(debug=True)