# Basics of Javascript

## Index, Value of Array

Remember than an Array is an object too

```js
let foods = ["Eba", "Egusi", "Iyana", "Amala"];

//  Get the keys of Object (Array is an Object too)
for (const f in foods) {
    console.log(f);         //Index :  0, 1, 2, 3
    console.log(foods[f]);  //Value: "Eba","Egusi","Iyana","Amala"
}

// // Get the Values of Object/Dict
for (const f of foods) {
    console.log(f); //Value: "Eba","Egusi","Iyana","Amala"
}


```


## Keys, Value of Dictionary

Get the Keys and Values of an Object of Dictionary
```js
let foods = {"Eba": 20, "Egusi":  5, "Iyana": 0, "Amala": 34};

//  Get the keys of Object/Dict
for (const f in foods) {
    console.log(f); //"Eba","Egusi","Iyana","Amala"
    console.log(foods[f]); // 20, 5, 0, 34

// Get the Values of Object/Dict
for (const f of Object.values(foods)) {
    console.log(f); // 20, 5, 0, 34
}

// Get the Values of Object/Dict
for (const f of Object.keys(foods)) {
    console.log(f); // Eba, Egusi, ...
}

// Get both index and value
const fruits = { orange: 3, mango: 13, banana: 5, apple: 21 }
  for (const [k, v] of Object.entries(fruits)) {
    console.log(k, v)
  } // orange 3, mango 13, banana 5, apple 21
console.log(Object.keys(foods)) // "Eba", "Egusi", ...
console.log(Object.entries(foods)) // ['Eba', 20], ['Egusi', 5] ...
```

## Filter

### Filtering - ARRAY

Filter Usage:

The basic syntax is const `newArray = originalArray.filter(callbackFunction)`.

The callbackFunction is executed for each element in the array and must return a boolean value:

- If it returns true, the element is included in the new array.
- If it returns false, the element is excluded

```js
/** Filtering An Array Of Numbers */
const numbers = [1, 2, 3, 4, 5, 6];

const evenNumbers = numbers.filter(num => num % 2 === 0);

console.log(evenNumbers);
// Output: [2, 4, 6]

console.log(numbers);
// Output: [1, 2, 3, 4, 5, 6] (original array remains unchanged)

//=================================
/** Filtering an Objects */

// find users where age is greater or equals 18
const users = [
  { name: 'Alice', age: 15 },
  { name: 'Bob', age: 22 },
  { name: 'Charlie', age: 18 },
  { name: 'David', age: 12 }
];

const adults = users.filter(person => person.age >= 18);

console.log(adults);


//================================
/** Search in Array of Strings */

 const fruits = ['orange', 'mango', 'banana', 'apple', 'grape']

  const searchValue = 'An'
  const searchFruits = fruits.filter((f) => f.toLowerCase().includes(searchValue.toLowerCase()))
  console.log(searchFruits) //  ['orange', 'mango', 'banana']

// BETTER STILL

  const fruits = ['orange', 'mango', 'banana', 'apple', 'grape']

// Aternatively use can use the lowercase type
// filterItems = (arr: string[], query: string)  ...
  const filterItems = (arr: Array<String>, query: String) => {
    return arr.filter((el) => el.toLowerCase().includes(query.toLowerCase()))
  }

  console.log('values : ', filterItems(fruits, 'An')) // ['orange', 'mango', 'banana']

```

### Filtering - OBJECT

```js
  // Filter Object
  const filtered = Object.entries(fruits).filter(([K, v]) => v > 5)
  console.log(filtered) // Array of Arrays: [[orange, 3],[mango, 13]]

  // Convert filtered Array back to Object
  const newFruits = Object.fromEntries(filtered)
  console.log(newFruits) // {mango: 13, apple: 21}
```

## Mapping example in javascript

```js
const numbers = [1, 2, 3, 4];

// Using map to double each number
const doubledNumbers = numbers.map(function(number) {
  return number * 2;
});

console.log(doubledNumbers); // Output: [2, 4, 6, 8]
console.log(numbers);       // Output: [1, 2, 3, 4] (original array unchanged)
```


## Basics of Export/import in Javascript

```html title="index.html"
<!DOCTYPE html>
<html>
  ...
  
    <body style="background-color: #333; color:#ddd">

        <h1>Testing out Promises</h1>
        <div id="demo"></div>

        <script src="index.js" type="module"></script>
    </body>
</html>
```

```js title="utility.js"
async function GetFile(filename){
    let filePromise = new Promise((resolve) 
    ...
    })

    // load the request data
    document.getElementById("demo").innerText = await filePromise
    console.log(filePromise)
}

function someFun01(){
    console.log("Hello From SomeFun 01")
}

function someFun02(){
    console.log("Hello from SomeFun 02")
}

export {GetFile, someFun01, someFun02}
```

```js title="index.js"
import {GetFile, someFun01} from './utility.js'

GetFile("./helloFile.html")
someFun01()
```

## Using Element.ClassList.toggle

It would simply allow you to do something like this:

```js

el.classList.toggle("abc", someBool);

// instead of this:

if (someBool) {
    el.classList.add("abc");
} else {
    el.classList.remove("abc");
}
```

## Stringfy a javascript Class

If the intention is to serialize only the data contained within a class instance, then `JSON.stringify()` can be used directly on the instance.

```js
class MyClass {
  constructor(name, age) {
    this.name = name;
    this.age = age;
    this.secret = "this will not be stringified by default"; // Non-enumerable
  }

  greet() {
    console.log(`Hello, my name is ${this.name}`);
  }
}

const instance = new MyClass("Alice", 30);
const jsonString = JSON.stringify(instance);
console.log(jsonString); // Output: {"name":"Alice","age":30}
```

To control the serialization process, particularly to include specific properties or transform values, a `toJSON()` method can be added to the class:

```js
class MyClassWithToJSON {
  constructor(name, age) {
    this.name = name;
    this.age = age;
    this.secret = "this will not be stringified by default";
  }

  greet() {
    console.log(`Hello, my name is ${this.name}`);
  }

  toJSON() {
    // Return a plain object with the desired properties for serialization
    return {
      personName: this.name,
      personAge: this.age,
      secretInfo: this.secret // Now including the 'secret' property
    };
  }
}

const instanceWithToJSON = new MyClassWithToJSON("Bob", 25);
const jsonStringWithToJSON = JSON.stringify(instanceWithToJSON);
console.log(jsonStringWithToJSON); 
/** Output: {
  "personName":"Bob",
  "personAge":25,
  "secretInfo":"this will not be stringified by default"}
  */
```

## ?? Nullish Coalescing Operator

In JavaScript, the `??` operator is called the **Nullish Coalescing Operator**.

It returns the right-hand side value only when the left-hand side is `null` or `undefined`. Otherwise, it returns the left-hand side.

### **basic syntax**

```js
const result = leftValue ?? defaultValue;
```

### Why use ?? instead of || (OR)?

The main reason to use ?? is to avoid bugs with `"falsy"` values like `0`, `""` (empty string), or `false`.

### **Example**

If a user has `0` points, `||` would incorrectly treat it as "nothing" and give them the default. `??` fixes this.

```js
// EXAMPLE 1 =======
const userScore = 0;

const finalScore1 = userScore || 10; // Result: 10 (Wrong!)
const finalScore2 = userScore ?? 10; // Result: 0  (Correct!)

// EXAMPLE 2 =======
const config = {
  animationEnabled: false,
  timeout: 0
};

// With ??, the actual values are preserved
const isEnabled = config.animationEnabled ?? true; // false
const delay = config.timeout ?? 300;               // 0

// EXAMPLE 3 =======
// If user or settings is missing, it falls back to 'dark'
const theme = user?.settings?.theme ?? 'dark';
```

## Using Map Example

```js
fruits = ["apple", "orange", "mango"] 
fruits.map((i)=>i[0].toUpperCase()+i.slice(1)) // First letter Cap.
//['Apple', 'Orange', 'Mango']

```

## Replacing Space in a String

1. Using `replaceAll()` (Recommended)
    This is the simplest modern method to replace every space in a string without using complex expressions.

    ```js
    const text = "hello world from js";
    const result = text.replaceAll(' ', '_');
    // Output: "hello_world_from_js"
    ```

2. Using `replace()` with Regex.
   If you use a standard string with `replace()`, it will only replace the first space. To replace all of them, use a Regular Expression with the global (g) flag.
   Standard spaces only: Use `/ /g`.All whitespace (tabs, newlines, etc.): Use `/\s/g`

   ```js
    const text = "hello world from js";
    const result = text.replace(/\s+/g, '_'); 
    const result = text.replace(/ /g, '_'); 
    // Output: "hello_world_from_js"
   ```

3. Use code with caution.3. Using `split()` and `join()`
  This is a classic "hack" that works in older browsers.
  You split the string into an array at every space and then join those array elements back together with an underscore.

  ```js
  const text = "hello world from js";
  const result = text.split(' ').join('_');
  // Output: "hello_world_from_js"
  ```

## Get Extension from filename

1. Using split() and pop() (Simplest)
    This is the most common one-liner for frontend JavaScript.
    It splits the string into an array at every dot and returns the last element.

    ```js
    const filename = "image.test.jpg";
    const extension = filename.split('.').pop();
    // Output: "jpg"
    ```

    **Warning: If there is no dot, it returns the entire filename.**

2. Using `substring()` and `lastIndexOf()` (Robust)
   This method is more reliable for handling edge cases, such as files with no extension or hidden files (like `.gitignore`).

    ```js
      function getExtension(filename) {
        const i = filename.lastIndexOf('.');
        return (i < 1) ? "" : filename.substr(i + 1);
      }

      console.log(getExtension("archive.tar.gz")); // "gz"
      console.log(getExtension(".gitignore"));     // "" (avoiding index 0)
      console.log(getExtension("README"));         // "" (no dot found)
    ```

3. Using Node.js `path.extname()`
   If you are working in a Node.js environment, use the built-in path module for the most accurate results.

   ```js
    const path = require('path');
    const extension = path.extname('index.html');
    // Output: ".html" (Note: includes the dot)
   ```

## Date Time in format YYYYMMDD_HHMMSS

To get the date and time in the YYYYMMDD_HHMMSS format using JavaScript,
you can use the toISOString() method or manual extraction for more control.

### Using toISOString() (Fastest)

This method leverages the standard ISO format and uses `replace()` to remove unwanted characters. 
Note that `toISOString()` always returns the time in UTC.

```javascript
const now = new Date();
const formatted = now.toISOString()
  .replace(/[-T:]/g, '')     // Remove -, T, and :
  .split('.')[0]             // Remove milliseconds
  .replace(/(\d{8})/, '$1_'); // Insert underscore after the 8th digit

console.log(formatted); // Example: "20260507_182845"
```

## Object Destructuring

**Destructuring assignment** is a special JavaScript syntax introduced in ES6 that allows you to "unpack" values from arrays or properties from objects directly into distinct variables. It makes your code cleaner, more readable, and reduces the need for repetitive boilerplate code

Object destructuring extracts values based on the **property keys** inside the object. *The variable names on the left must match the key names on the right*

### Example 1

```js
const user = {
  name: "Alex",
  age: 28,
  country: "Nigeria"
};

// 1. Basic Destructuring
const { name, age } = user;
console.log(name); // "Alex"
console.log(age);  // 28

// 2. Renaming Variables (Using Aliases)
const { country: userLocation } = user;
console.log(userLocation); // "Nigeria"

// 3. Setting Default Values (Falls back if property doesn't exist i.e. undefined)
const { theme = "dark", lang } = user;
console.log(theme); // "dark"
console.log(lang); // "undefined"

```

### Example 2

Let's say we have some deeply nested data like we might get back from a JSON api:

```js
const wes = {
  first: 'Wes',
  last: 'Bos',
  links: {
    social: {
      twitter: 'https://twitter.com/wesbos',
      facebook: 'https://facebook.com/wesbos.developer',
    },
    web: {
      blog: 'https://wesbos.com'
    }
  }
};
```

I want to be able to pull out Twitter and Facebook URLs here. I could do this like it's 1994 and we're all running around with walkmans:

```js
const twitter = wes.links.social.twitter;
const facebook = wes.links.social.facebook;
// Annoying!
```

We can use destructuring to do it one better!

```js
const { twitter, facebook } = wes.links.social;
console.log(twitter, facebook); // logs the 2 variables
```


## Array Destructuring

Array destructuring extracts values based on their **position (index)** in the array. You use square brackets on the left side of the assignment

```js
const colors = ["red", "green", "blue"];

// 1. Basic Destructuring
const [firstColor, secondColor] = colors;
console.log(firstColor);  // "red"
console.log(secondColor); // "green"

// 2. Skipping Elements (Leave an empty space between commas)
const [primary, , tertiary] = colors;
console.log(primary);  // "red"
console.log(tertiary); // "blue"



```

## You Spread operator and Rest Operator

The spread operator in JavaScript can be very useful.
For example to create a copy of an object:

```js
const firstObject = {id: 0, name: 'John'};
const secondObject = {...firstObject};

console.log(firstObject);
console.log(secondObject);

// { id: 0, name: 'John'}
// { id: 0, name: 'John'
```

## Using Rest operator on Array and Object

But did you know you can also use rest operation( ... on the left side or as param) to exclude an object property?

```js

// *** ARRAY REST OPERATOR
const colors = ["red", "green", "blue"];
// 3. Using the Rest Parameter (... syntax to collect remaining items)
const [first, ...restOfColors] = colors;
console.log(first);        // "red"
console.log(restOfColors); // ["green", "blue"]

// *** OBJECT REST OPERATOR
const userDetails = {id: 0, firstName: 'John', lastName: 'Smith', age: 77 };

// take every property except age:
const {age,     ...userInfoPrivacy } = userDetails;
const {age, id, ...userBasicInfo} = userDetails; 

console.log(userDetails); // { id: 0, firstName: 'John', lastName: 'Smith', age: 77 }
console.log(userInfoPrivacy); // { id: 0, firstName: 'John', lastName: 'Smith' }
console.log(userBasicInfo); // {firstName: 'John', lastName: 'Smith'}

```
!!! note
    `age` and `id` variable is still accessible within the scope.

## Advance use case

### Function Parameter Destructuring
Instead of passing an entire object to a function and using dot notation everywhere, you can destructure the properties directly inside the function signature

```js
const product = { id: 101, title: "Laptop", price: 999 };

function displayProduct({ title, price }) {
  console.log(`${title} costs $${price}`);
}

displayProduct(product); // "Laptop costs $999"

```

### Swapping Variables

You can swap the values of two variables in a single line without using a temporary third variable

```js
let a = 1;
let b = 5;

[a, b] = [b, a];

console.log(a); // 5
console.log(b); // 1

```