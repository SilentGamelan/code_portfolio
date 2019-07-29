from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """ Displays users current portfolio and net worth """

    display_name = db.execute("SELECT username FROM users WHERE :current_user=user_id", current_user=session["user_id"])
    current_portfolio = db.execute("SELECT symbol as stock_symbol, shares_owned, 0.0 AS current_pps, 0.0 AS holding_value, DATETIME('now') AS dt FROM portfolios WHERE :current_user=user_id", current_user=session["user_id"])
    cash = get_balance()
    stocks_total = 0
    grand_total = 0

    if len(current_portfolio) > 0:
        stocks_total = 0.0
        for row in current_portfolio:
            quote = mylookup(row["stock_symbol"])
            # DEBUG - temp measure re: server-side lookup problem
            if not quote:
                return apology("Error: lookup server not responding")
            ##
            row["current_pps"] = quote["price"]
            row["holding_value"] = row["current_pps"] * row["shares_owned"]
            stocks_total += row["holding_value"]


        grand_total = cash + stocks_total


    return render_template("index.html", current_portfolio=current_portfolio, stocks_total=stocks_total,
                            cash_total=cash, grand_total = grand_total, display_name=display_name[0]["username"])

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock.
    NB: error message must contain "error" in order for buy_logic() to return problems picked up during validation
    """
    current_funds = get_balance()


    if request.method == "POST":
        routing_msg = request.form.get("routing_msg")
        stock_name = request.form.get("stock_name")
        stock_price = request.form.get("stock_price")
        stock_symbol = request.form.get("stock_symbol").upper()
        stock_amount = request.form.get("stock_amount")

        total_value = value_totaller(stock_price, stock_amount)

        # using routing_msg to select the appropriate logic below, as it identifies the source of the request
        # The "Error" in x error checking is brittle; case-sensitive and depends on all apology messages starting with "Error"
        if routing_msg == "BUY":
            result = validate_buy(stock_symbol, stock_amount, routing_msg)
            # had to alter this, as helpers.py was changed to automatically give numerical codes as top-message
            if "Error" in result:
                return result
            else:
                session["invoice"] = result
                return redirect(url_for("invoice"))

        elif routing_msg == "UPDATE" or routing_msg == "QUOTE":
            result = validate_buy(stock_symbol, stock_amount, routing_msg)
            return result
        else:
            return apology("Internal Error", "Please Try Again")

    else:
        return render_template("buy.html", current_funds=current_funds)


@app.route("/invoice")
@login_required
def invoice():
    """ Wrapper for displaying invoices.
    Redirecting to this page from buy/sell and using a session variable "invoice" set before call avoids problems with transactions
    being repeated if user refreshes or pages-back on invoice screen
    """

    if session["invoice"]:
        invoice = session["invoice"]
        session["invoice"] = None
        return render_template("invoice.html", invoice=invoice)

    else:
        return redirect(url_for("index"))


def validate_buy(stock_symbol, stock_amount, routing_msg):
    if stock_symbol == "":
        return apology("Error: Please enter a stock symbol")

    quote = mylookup(stock_symbol)

    if quote is None:
        return apology("Error: Stock Symbol not found", stock_symbol)

    stock_name=quote['name']
    stock_price=quote['price']
    stock_symbol=quote['symbol']

    if stock_amount and int(stock_amount) < 1:
        return apology("Error: Stocks to buy must be a positive number")

    total_value = value_totaller(stock_amount, stock_price)

    current_funds = get_balance()

    # Kludge to work around fact that when buying without updating prices from vanilla buy page,
    # the values required to process the transaction are missing.
    #   As there is no "update" rendering of buy.html, this values aren't being passed as render_template arguments
    #   I have altered the code to pass back the necessary values.
    #   This requires some checking in the buy() function that goes against my attempt to encapsulate the logic as neatly
    #   as possible in descriptive functions. I'm not happy about it , but will live with for it to work

    if routing_msg == "BUY":
        result = buy_logic(stock_symbol, stock_name, stock_price, stock_amount)
        return result
    else:
        validated_values = render_template("buy.html", stock_name=stock_name, stock_price=stock_price,
                            stock_symbol=stock_symbol, stock_amount=stock_amount,
                            current_funds=current_funds, total_value=total_value, msg="updated")
        return validated_values


def buy_logic(stock_symbol, stock_name, stock_price, stock_amount):


    if not stock_amount:
        return apology("Error: Please enter amount of stock to buy")
    elif int(stock_amount) < 1:
        return apology("Error: Invalid stock amount")

    # have rearranged this so not passed in from calling function, to minimize window in which two requests could be submitted
    # (eg; from different browsers) and possible to buy with out-of-date balance
    current_funds = get_balance()

    total_value = value_totaller(stock_price, stock_amount)

    if total_value > current_funds:
        return apology("Error: Not enough cash")
    else:
        new_balance = current_funds - total_value
        receipt = transaction_engine(stock_symbol, stock_price, stock_amount, new_balance, "BUY")

    # May need to reverse transaction stages if hit an error part-way through transaction_engine()
    # Probably best to create 3 tuples to hold the pre-processed states of all 3 tables, and write them back in on error?
    # transaction_type = VOID

    return receipt


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    # TODO - divide hits into separate pages (eg; 20 results to a page)
    user_history = db.execute("SELECT transaction_id, symbol, pps, shares_amount, pps*shares_amount AS total, transaction_type, transaction_date FROM transactions WHERE user_id = :current_user ORDER BY transaction_date DESC", current_user=session["user_id"])

    return render_template("history.html", user_history=user_history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""


    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # forget any user_id - have moved inside IF to avoid dumping flashed messages on redirects
        session.clear()

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["user_id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        # if session data contains user_id, user is already logged in, so redirect with message
        # if throws a KeyError, not logged in so continue with login process
        try:
            session["user_id"]
            flash("Already logged in!")
            return apology("Must Log Out", "Before Logging In")
        except KeyError:
            return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # DEBUG - assigned var from (request.form.get("stock_name")) while diagnosing server-side lookup() error
        stock_name = request.form.get("stock_symbol")
        quote = mylookup(stock_name)
        if quote:
            return render_template("quoted.html", stock_name=quote['name'], stock_price=quote['price'], stock_symbol=quote['symbol'])
        else:
            return apology("Error: Does not appear to be a valid stock symbol")

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    if request.method=="POST":
        registration_error = None

        if not request.form.get("username"):
            registration_error = "You must enter a username to register"

        elif db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            registration_error = "Sorry, username already exists"

        elif not request.form.get("password") or not request.form.get("password_check"):
            registration_error = "You must enter your password in both boxes"

        elif request.form.get("password") != request.form.get("password_check"):
            registration_error = "Both passwords must match"

        # if no registration_error exists, then r egistration successful
        if registration_error:
            return(apology(registration_error))
        else:
            db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)",
                        username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))
            flash('You were successfully registered!')
            return redirect(url_for("index"))


    else:
        # if session data contains user_id, user is already logged in, so redirect with message
        # if throws a KeyError, not logged in so continue with login process
        try:
            session["user_id"]
            flash("Cannot register another account while logged in")
            return redirect(url_for("index"))
        except KeyError:
            return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock

    """
    current_portfolio = db.execute("SELECT symbol as stock_symbol, shares_owned, 0.0 AS current_pps, 0.0 AS holding_value, DATETIME('now') as dt FROM portfolios WHERE :current_user=user_id", current_user=session["user_id"])

    stocks_total = 0.0
    for row in current_portfolio:
        quote = mylookup(row["stock_symbol"])
        # DEBUG - temp measure to catch server-side lookup error
        if not quote:
            return apology("Error: lookup server not responding")
        ##
        row["current_pps"] = quote["price"]
        row["holding_value"] = row["current_pps"] * row["shares_owned"]
        stocks_total += row["holding_value"]

    display_name = db.execute("SELECT username FROM users WHERE :current_user=user_id", current_user=session["user_id"])
    cash = get_balance()
    grand_total = 0.0

    if request.method == "POST":
        routing_msg = request.form.get("routing_msg")
        selected = request.form.get("radioGroup") # Maintains which stock is selected between page updates
        sale_quantity = request.form.get("sale_quantity")
        if not sale_quantity:
            sale_quantity = 0
        else:
            sale_quantity = int(sale_quantity)

        sale_value = 0

        if selected:
            quote = mylookup(selected)
            # DEBUG - temp measure to catch server-side lookup error
            if not quote:
                return apology("Error: lookup server error not responding")
            else:
                stock_price = quote["price"]
                sale_value = value_totaller(stock_price, sale_quantity)
                sale_total = cash + stocks_total

        if routing_msg == "SELL":

            if not selected:
                return apology("Please select stock", "to sell")

            if not sale_quantity:
                return apology("Please Enter sale quantity")

            result = validate_sale(selected, sale_quantity)
            if "Error" in result:
                return result

            new_balance = cash + sale_value
            result = transaction_engine(selected, stock_price, sale_quantity, new_balance, "SELL")
            session["invoice"] = result
            return redirect(url_for("invoice"))

        elif routing_msg == "UPDATE":

            #if selected:
            return render_template("sell.html", current_portfolio=current_portfolio, stocks_total=stocks_total,
                                        cash_total=cash, grand_total = grand_total, display_name=display_name[0]["username"],
                                        selected = selected, sale_value=sale_value, sale_quantity=sale_quantity)
        else:
            return apology("Internal Error", "Routing MSG missing")

    else:
        return render_template("sell.html", current_portfolio=current_portfolio, stocks_total=stocks_total,
                            cash_total=cash, grand_total = grand_total, display_name=display_name[0]["username"])

def validate_sale(selected, sale_quantity):
    """ Check have sufficient stocks to sell """
    shares_owned = db.execute("SELECT shares_owned FROM portfolios WHERE :current_user = user_id AND symbol = :selected",
                                current_user=session["user_id"], selected=selected)
    if len(shares_owned) == 0:
        return apology("Error: You don't own any of that stock")
    elif sale_quantity > shares_owned[0]["shares_owned"]:
        return apology("Error: not enough shares")
    else:
        return "OK"



    # TODO - reroute both buy and sale to go immediately from validate->transaction_engine
    # only need to pass in symbol, stock_amount, transaction_type?
    # do the sql calls inside transaction_engine, otherwise duplicating effort
    # That way, any errors will be returned back up to the view call, else do the redirect to receipt from end of transaction_engine

@login_required
def get_balance():
    """ do SQL lookup on current funds, and return correctly formatted value """
    balance = db.execute("SELECT cash FROM users WHERE user_id = :current_user", current_user=session["user_id"])
    return balance[0]["cash"]

def value_totaller(stock_price, stock_amount):
    """ need a wrapper to handle price or amount NONE or 0 (multiply by zero error)
        Neater to use a function rather than another if-else in buy()
    """
    # Need to coerse types as these values are being held in type="hidden" fields on buy.html
    # cannot set type as both "hidden" and "number"; hidden values seem to default to being text
    # NB: also had similar problem in sell.html - explains why they're hidden there too.
    if stock_price and stock_amount:
        return float(stock_price) * int(stock_amount)
    else:
        return 0

def transaction_engine(stock_symbol, stock_price, stock_amount, new_balance, transaction_type):
    """ handles SQL execution for buy/sell """
    # TODO - sort out error checking and transaction-roll back logic
    error_msg = "E"
    current_user = session["user_id"]
    error_msg = db.execute("UPDATE users SET cash = :new_balance WHERE user_id = :user",
                new_balance=new_balance, user=current_user)

    transaction_key = db.execute("INSERT into transactions (user_id, symbol, pps, shares_amount, transaction_type)\
                VALUES (:user_id, :symbol, :pps, :shares_amount, :transaction_type)", \
                user_id=session["user_id"], symbol=stock_symbol, pps=stock_price, shares_amount=stock_amount, \
                transaction_type=transaction_type)

    current_transaction = db.execute("SELECT shares_owned FROM portfolios WHERE user_id = :user AND symbol= :symbol",
                                            user=current_user, symbol=stock_symbol)

        # copy information into portfolio
    if transaction_type == "BUY":
        # TODO - exception handling
        # Is this the best pattern to use, as the execute statements may rethrow an exception.
        #
        # If required, think need to catch the exception by cs50.SQL.[ERRORTYPE]


        if len(current_transaction) > 0:
            db.execute("UPDATE portfolios SET shares_owned = :shares_owned WHERE user_id=:user AND symbol=:symbol",
                        shares_owned=current_transaction[0]["shares_owned"]+int(stock_amount), user=current_user, symbol=stock_symbol)
        else:
            db.execute("INSERT into portfolios(user_id, symbol, shares_owned) VALUES(:user_id, :symbol, :shares_owned)",
                        user_id=current_user, symbol=stock_symbol, shares_owned=stock_amount)

    else:
        updated_share_amount = current_transaction[0]["shares_owned"]-int(stock_amount)
        if updated_share_amount > 0:
            db.execute("UPDATE portfolios SET shares_owned = :shares_owned WHERE user_id=:user AND symbol=:symbol",
                        shares_owned=updated_share_amount, user=current_user, symbol=stock_symbol)
        else:
            db.execute("DELETE FROM portfolios WHERE user_id=:user AND symbol=:symbol", user=current_user, symbol=stock_symbol)



    return db.execute("SELECT transaction_id, username, symbol, pps, shares_amount, pps*shares_amount AS total, transaction_date FROM users JOIN transactions on users.user_id=transactions.user_id WHERE transaction_id = :transaction_id",
                        transaction_id=transaction_key)


def mylookup(stock_name):
    """ problems with alphavantage sometimes not responding to requests. tries twice before failing.
        where possible have included code in calling functions to detect and report look-up error
    """

    result = lookup(stock_name)
    if result:
        return result
    else:
        result = lookup(stock_name)

    return result

@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():


    if request.method=="POST":
        old_pw = request.form.get("current_pw")
        new_pw1 = request.form.get("new_pw1")
        new_pw2 = request.form.get("new_pw2")

        old_hash = db.execute("SELECT hash FROM users WHERE user_id = :current_user", current_user = session["user_id"])

        if pwd_context.verify(old_pw, old_hash[0]["hash"]) and new_pw1 == new_pw2:
            new_hash = pwd_context.hash(new_pw1)
            try:
                result = db.execute("UPDATE users SET hash = :hash WHERE user_id = :current_user", current_user=session["user_id"], hash=new_hash)
            except RuntimeError:
                return apology("Ooops, something went wrong")

            if result is None or result != 1:
                return apology("Error: DB was not updated")
            else:
                flash("Success - password updated")
                return redirect(url_for("index"))
        else:
            flash("new passwords did not match")
            return redirect(url_for("settings"))


    else:
        return render_template("settings.html")

