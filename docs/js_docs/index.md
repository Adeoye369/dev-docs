# Basics of Javascript

## Index, Value of Array

Remember than an Array is an object too

```js
let foods = ["Eba", "Egusi", "Iyana", "Amala"];

//  Get the keys of Object (Array is an Object too)
for (const f in foods) {
    console.log(f); //"Eba","Egusi","Iyana","Amala"
    console.log(foods[f]); // Get the Values
}

// // Get the Values of Object/Dict
for (const f of foods) {
    console.log(f);
}
```


## Keys, Value of Dictionary

Get the Keys and Values of an Object of Dictionary
```js
let foods = {"Eba": 20, "Egusi":  5, "Iyana": 0, "Amala": 34};

//  Get the keys of Object/Dict
for (const f in foods) {
    console.log(f); //"Eba","Egusi","Iyana","Amala"
    console.log(foods[f]); // Get the Values
}

// Get the Values of Object/Dict
for (const f of Object.values(foods)) {
    console.log(f); // 20, 5, 0, 34
}

console.log(Object.keys(foods)) // "Eba", "Egusi", ...
console.log(Object.entries(foods)) // ['Eba', 20], ['Egusi', 5] ...
```