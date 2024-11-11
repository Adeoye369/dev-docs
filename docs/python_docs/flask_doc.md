# Flask Backend Frame work doc

Quick start with flask

```py
from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello_world():
    return "<p> Hello Flask</p>"
```

To run your flask you do `flask --app [file_path] run`
an example is this  `flask --app ./day54-webback1/main run`

## Basic Runing with having to use cmd

```py
from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello_world():
    return "<p> Hello Flask</p>"

@app.route('/user')
def user_page():
    return "<h2> This User </h2>"

@app.route('/user/<name>/<float:price>')
def cost_page(name, price):
    return f"""
<ul>
    <li> {name} : <span>{price}</span></li>
    <li> {name} : <span>{price*2}</span></li>
<ul>
"""

if __name__ == "__main__":
    app.run(debug=True)
```

![Quick Demo.](img/image-39.png)

## Render html and css with `render_template`

in your project directory, you need to have the follow folders:

- `static` folder - this is where your images and css are located.
- `templates` folder - this is where you html files are located


Once you have that the following code can be executed:

```py title="server.py"
from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def hello_world():
    return render_template("index.html") # call the html in template


if __name__ == "__main__":
    app.run(debug=True)

```

```html
<!DOCTYPE html>
...
    <!-- NOTE that stytle is in "static" directory  -->
    <link rel="stylesheet" href="static/style.css">
    <title>Adeoye</title>
</head>
<body>
    <main class="main-title">
        <div class="details">
            <h2>Adegbite Adeoye</h2>
            <p>Story Artist | Software Dev.</p>
        </div>
    </main>
    
</body>
</html>
```
<div class="grid" markdown>

<figure markdown="span" style="max-width: 200px">
![alt text](img/image-40.png)
</figure>

<figure markdown="span" style="width: 500px">
![alt text](img/image-41.png)
</figure>


</div>



