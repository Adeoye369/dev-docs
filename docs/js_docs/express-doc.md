# Getting Started with Express

Running basic `get`

```js
import express from 'express';
// express = require("express");
const app = express();


// Arg: path_url, callback function
app.get('/', (req, res)=>{
    res.send("Hello from Express");
});

// Creating more route
// Creating more route
app.get('/api/playlist', (req, res)=>{
    res.send({song1: "ahala", song2: "holoa way"});
})

// Pass callback to display on console
app.listen(3000, ()=>{
    console.log("listening on port 3000...")
});

```
![alt text](img/image-3.png)

Note install `nodemon` package to avoid having to restart everytime

`npm i -g nodemon` 

## creating environment variable for the Port

```js
// PORT for server
const port = process.env.PORT;
app.listen(port, ()=>{
    console.log(`listening on port ${port}..`)
});
```

set environment variable

`>>> $env:PORT=5000`

## Route Parameters

```js
// Defining a parameter in a route
app.get('/api/playlist/:idx', (req, res)=>{
    res.send(req.params.idx);
})
```

### Reading multiple Params

```js
// reading multiple params
app.get("/api/user/:year/:month", (req, res)=>{
    res.send(req.params);
});
```
<figure markdown='span'>
    ![alt text](img/image-6.png)
</figure>


## Reading Query Parameters

```js
// reading Query params
app.get("/api/song", (req, res)=>{
    res.send(req.query);
})
```

<figure markdown='span'>
    ![alt text](img/image-5.png)
</figure>

## Handing GET in express

```js
const courses = [
    {id:1, name : "Math"},
    {id:2, name : "English"},
    {id:3, name : "Further Math"},
];

// Arg: path_url, callback function
app.get("/", (req, res)=>{
    res.send("Hello from Express");
});

// course route
app.get('/api/courses', (req, res)=>{
    res.send(courses);
 })

// course route handling get
app.get('/api/courses/:id', (req, res)=>{
   let course = courses.find(c=>c.id === parseInt(req.params.id))
   if(!course) res.status(404).send('The given course ID not found');
   res.send(course);
})

```

## Basics of POST in express

```js
const courses = [
    {id:1, name : "Math"}, 
    {id:2, name : "English"},
    {id:3, name : "Further Math"},
];

...

app.use(express.json()); // Add middleware 

app.post('/api/courses', (req, res)=>{
    let course = {
        id : courses.length + 1,
        name : req.body.name
    };

    // Add to database
    courses.push(course);

    // send new course for user to see
    res.send(course);
});
```

### Input Valiation using Joi

Make sure you have postman vscode install

```js
// ============ POST ===================

import Joi from 'joi';

app.use(express.json()); // Add middleware 

app.post('/api/courses', (req, res)=>{

    const schema = Joi.object({name: Joi.string().min(3).required()});
    
    //using spread operator on `req.error` to get `error`
    const {error} = schema.validate(req.body); 
    
    if(error) {
        res.status(400).send(error.details[0].message);
        return;
    }

    let course = {
        id : courses.length + 1,
        name : req.body.name
    };

    // Add to database
    courses.push(course);

    // send new course for user to see
    res.send(course);
});
```
<div class='grid' markdown>
    
<figure markdown='span'>
    ![alt text](img/image-7.png)
</figure>

<figure markdown='span'>
    ![alt text](img/image-8.png)
</figure>
</div>
