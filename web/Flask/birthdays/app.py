import sqlite3
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Database setup
DATABASE = "birthdays.db"

# Function to interact with database
def query_db(query, args=(), one=False):
    with sqlite3.connect(DATABASE) as conn:
        conn.row_factory = sqlite3.Row
        cur = conn.execute(query, args)
        rv = cur.fetchall()
        conn.commit()
    return (rv[0] if rv else None) if one else rv

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Retrieve form data
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Validate input
        if name and month and day:
            query_db("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", (name, month, day))
        
        return redirect("/")

    else:
        # Retrieve all birthdays from the database
        birthdays = query_db("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)
