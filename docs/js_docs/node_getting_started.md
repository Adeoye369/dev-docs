# Basics of NodeJs

## intro `hello node`

First node code

```js
console.log("Hello node");
```
in console run : `node dir/index.js`


## copying file in node

This will copy the file in our current directory

```js
const fs = require("fs")

fs.copyFileSync("file1.txt", "file2.txt")
```

![alt text](img/image.png)

## Using the basic express js

```js
import express from 'express'

const app = express()

app.get('/', (req, res) =>{
  res.send('Hello World')
})

app.listen(3000)
```
<figure markdown="span">
![alt text](img/image-1.png){width=50%}
</figure>
<hr>

## Basic Import/export in NodeJs

This demonstrate import using both commonjs(cjs) and Esmacript 6(es6) syntax

=== "es6"

    ```js title="utils.js"
    export function randNumGen(){
        return Math.floor(Math.random() * 100) + 1;
    }
    ```

    ```js title="index.js"
    import { randNumGen } from "./utils.js";
    console.log(randNumGen());
    ```


=== "cjs"

    ```js title="utils.js"
    function randNumGen(){
        return Math.floor(Math.random() * 100) + 1;
    }
    module.exports = randNumGen;
    ```

    ```js title="index.js"
    randNumGen = require("./utils");
    console.log(randNumGen());
    ```

!!!Note
    When export using the ES6 module you can use this two option

    ```js
    // A - utils.js - attact export to function
    export function randNumGen(){...}

    // B - utils.js - put function object at end
    function randNumGen(){...} 
    export {randNumGen};

    // For both of this scenerio, use {} when import
    // index.js
    import {randNumGen} from 'utils.js'
    ```
   
    Export with `default` option
    ```js
    
    function randNumGen(){...}
    export default randNumGen;

    // index.js - Here you don't need to add {}
    import randNumGen from 'utils.js'

    ```

To export multiple function export

=== "es6"

    ```js title="utils.js"
    function randNumGen(){
    return Math.floor(Math.random() * 100) + 1;}

    function getBMI(mass, height){
    return (mass/ Math.pow(height, 2));}

    export {randNumGen, getBMI};
    ```

    ```js title="index.js"
    import {randNumGen, getBMI} from "./utils.js";

    console.log(`Get random ${randNumGen()}`);
    console.log(`Get BMI: ${getBMI(100, 30)}`);
    ```


=== "cjs"

    ```js title="utils.js"
    function randNumGen(){
    return Math.floor(Math.random() * 100) + 1;}

    function getBMI(mass, height){
        return (mass/ Math.pow(height, 2));}

    module.exports = {randNumGen, getBMI};
    ```

    ```js title="index.js"
    const {randNumGen, getBMI}  = require("./utils");

    console.log(`Get random ${randNumGen()}`);
    console.log(`Get BMI: ${getBMI(100, 30)}`);
    ```