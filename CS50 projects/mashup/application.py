import os
import re
from flask import Flask, jsonify, render_template, request, url_for
from flask_jsglue import JSGlue

from cs50 import SQL
from helpers import lookup

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")

# Check to see if FTS virtual table is present
dbase = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='fts_table'")

# If virtual table not found, recreate it
if not dbase:
    dbase = db.execute("CREATE VIRTUAL TABLE IF NOT EXISTS fts_table USING fts4(content='places', notindexed=country_code, \
                            notindexed=admin_name2, notindexed=admin_name3, notindexed=admin_code2, notindexed=admin_code3, \
                            notindexed=latitude, notindexed=longitude, notindexed=accuracy, tokenize='simple')")

# Was having some problems with not receiving any results from virtual table, found forum post that advised rebuilding - worked
dbase = db.execute("INSERT INTO fts_table(fts_table) VALUES('rebuild')")
dbase = db.execute("INSERT INTO fts_table(fts_table) VALUES('optimize')")


@app.route("/")
def index():
    """Render map."""
    if not os.environ.get("API_KEY"):
        raise RuntimeError("API_KEY not set")
    return render_template("index.html", key=os.environ.get("API_KEY"))

@app.route("/articles")
def articles():
    """Look up articles for geo."""

    geo = request.args.get("geo")

    articles = lookup(geo)

    return jsonify(articles)

@app.route("/search")
def search():
    """Search for places that match query."""
    # Uses Full Text Search v4 SQLITE extension  to allow tokenization and FTS search - populate from current db

    # I was originally going to manually tokenize the search query 'q' and simple pre-processing before submitting the SQL query:
    #
    # only tokenize first 6 words from q, ignore longer queries as too complex - 1 x postcode, 3 x place name, 2 x state
    # ie; Most words in a placename = 3, state names = 2 max
    #
    # Postcode take priority, then place name, then state during search. Only accept ONE postcode.
    #
    # When tokenizing, if a numeric token is found [zip code] ignore all other numerical tokens from q or make them blank ""
    #
    # FTS booleans have to occur INSIDE the query string "moo AND boo NOT poo" - must construct a new string
    # such as "token1 AND postcode" or "postcode AND token2", using token[x] and separate postcode variable.
    #
    # !! Appears that the FTS pretty much achieves this functionality in terms of narrowing down even partial matches without having
    # !! to form a boolean query. # "re al 9" returns "Red Devil, Alaska, 99656"
    # !! Will leave the input sanitisation and removal of extra postcodes, and comment out redundant code in case it comes in useful
    # !! for other uses of SQL FTS

    try:
        q = request.args.get("q")
    except TypeError:
        print("Error: missing search query")
        return(jsonify([]))
    else:

        # Tokenize and lightly sanitise input by replacing any likely non-alphanum chars
        tokens = re.sub('[^0-9a-zA-Z]+', ' ', q).split(" ")

        # If any more than 1 numeric token, eliminate the rest (only want to consider one postcode)
        PC_FOUND = False
        for token in tokens:
            if token.isdigit():
                if PC_FOUND is False:
                    PC_FOUND = True
                    # below not needed any more - Don't need to isolate postcode now have FTS wildcard searches working
                    # postcode = token
            else:
                token = ""

#        Also not needed - originally to prevent index out of range errors by packing empty values up to max token length
#        (SQL query would have made of FTS booleans comparing between "postcode AND token[x]" OR "postcode AND token[y]" etc
#
#       lenny = len(tokens)
#       if lenny < 6:
#            for x in range(lenny,6):
#                tokens.append("")
#        print(tokens)
#

        if len(tokens) == 1:
            tokenated = tokens[0] + "*"
        else:
            tokenated = "* ".join(tokens) + "*"
        print("Tokenated: ", tokenated)

        #!!! HERE !!! trying to remove all extraneous digit-only tokens, to simplify prioritising post code
        # Then need to combine wildcard search with each token in FTS SQL query
        # JUST NEED TO .join the non-blank tokens after extra postcodes removed and add "* " as a separator??


        #tokens = "* OR ".join(tokens)
        #print(tokens)

        rows = db.execute('SELECT * FROM fts_table WHERE fts_table MATCH :tokenated LIMIT 10', tokenated=tokenated);

        return jsonify(rows)

@app.route("/update")
def update():
    """Find up to 10 places within view."""

    # ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # explode southwest corner into two variables
    (sw_lat, sw_lng) = [float(s) for s in request.args.get("sw").split(",")]

    # explode northeast corner into two variables
    (ne_lat, ne_lng) = [float(s) for s in request.args.get("ne").split(",")]

    # find 10 cities within view, pseudorandomly chosen if more within view
    if (sw_lng <= ne_lng):

        # doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # output places as JSON
    return jsonify(rows)
