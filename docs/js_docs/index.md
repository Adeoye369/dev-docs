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
