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

