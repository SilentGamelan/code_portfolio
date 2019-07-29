from flask import Flask, redirect, render_template, request, url_for
import os, sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/notweets")
def notweets():
    # screen_name is being passed as a querystring (/?=foobar) - this can be parsed back into variable by request.args.get
    screen_name = request.args.get('screen_name')

    # will harmlessly redirect back to main page is user tries to manually access /notweets
    if screen_name is None:
       return render_template("index.html")
    else:
        return render_template("notweets.html", screen_name=screen_name)


@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    # redirect to error page if no user found/tweets protected
    if tweets is None:
        return redirect(url_for("notweets", screen_name=screen_name))


    positives = os.path.join(sys.path[0], 'positive-words.txt')
    negatives = os.path.join(sys.path[0], 'negative-words.txt')

    analyzer = Analyzer(positives, negatives)

    # TODO
    positive, negative, neutral = 0.0, 0.0, 0.0
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score < 0:
            negative += 1
        elif score > 0:
            positive += 1
        else:
            neutral += 1

    # Find percentages of sentiments - using len(tweets) should give correct results even if user tweets < 100
    positive = (positive / len(tweets)) * 100
    neutral = (neutral / len(tweets)) * 100
    negative = (negative / len(tweets)) * 100

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
