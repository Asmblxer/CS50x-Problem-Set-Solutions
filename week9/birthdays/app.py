from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


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

        # TODO: Add the user's entry into the database
        # Access form data
        name = request.form.get("name")
        if not name: return redirect("/")

        month = request.form.get("month")
        if not month: return redirect("/")
        try: month = int(month)
        except ValueError: return redirect("/")
        if month < 1 or month > 12: return redirect("/")

        day = request.form.get("day")
        if not day: return redirect("/")
        try: day = int(day)
        except ValueError: return redirect("/")
        if day < 1 or day > 31: return redirect("/")

        # Insert data into database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        # Query for all birthdays
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render birthdays page
        return render_template("index.html", birthdays=birthdays)


@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")


@app.route("/edit", methods=["POST"])
def edit():
    id = request.form.get("id")
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if id and name and month and day:
        try:
            month = int(month)
            day = int(day)
            if 1 <= month <= 12 and 1 <= day <= 31:
                db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
                          name, month, day, id)
        except ValueError:
            pass
    return redirect("/")


if __name__ == '__main__':
    app.run(debug=True)

