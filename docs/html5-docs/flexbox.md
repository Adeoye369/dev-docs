# Flexbox Doc

Flex is a better way of setting up your webpage layout display or a more comtemporary way of setting it up for responsiveness.

### Setting display `flex` and gap

<div class="grid" markdown>

```css
.container {
    display: flex;
    gap: 5px;
}

.section{
    background-color: #eee;
    padding: 5px;
}
```

```html
<div class="container">
<section class="section">
Lorem ipsum dolor sit amet, ... 
</section>

<section class="section">
Aliquam erat volutpat. Nullam ...
</section>

<section class="section">
Curabitur varius sagittis quam, ...
</section>
</div>
```

Before `flex`
![alt text](img/image-39.png)

After `flex`
![alt text](img/image-40.png)
</div>

- By default, `flex` container displays its element in a **column format**.
- Flex will try to display all of your content no matter the content ('div', 'span', 'images') in one line while putting into consideration the content of the html elements.
  
<figure markdown>
![alt text](img/image-41.png)
</figure>

### Setting up  display `inline-flex`

Just like when you have display block, and inline-block, by default flex container is a kind of block form. so you can so set it to `inline-flex`

```css
.container {
    display: inline-flex;
    gap: 5px;
    border: 2px dashed green;
}

```

before
![alt text](img/image-42.png)

after
![alt text](img/image-43.png)

#### Example - Work with flex and Justify

What we know so far
```css
nav > ul{
background-color: orange;
display: flex; gap:5px; 
height: 40px;
}
```
![alt text](img/image-45.png)

With `justify-content` you can have more flexiblity in the content

```css
nav > ul{
background-color: orange;
display: flex; gap:5px; 
height: 40px;
justify-content: center; /* center ther content of container */
}
```
![alt text](img/image-44.png)

## Setting the Flex direction

This is basically the **direction** along which flex is stacking up the html elements. By default `flex-direction` is set to `row` this is the  **Main axis,** which is along **X-axis**. Here the **Cross axis** is along the **Y-axis** 

```css
/* This is the default behaviour */
 section.color{
display:flex; 
background-color: aquamarine;   
margin-top: 20px;        
}

section.color > div{
border: 1px solid #eee;
width: 100%; height: 50px;
}
```
![alt text](<img/Screenshot 2024-11-03 162159.png>)

The second and obvious alternative is setting the `flex-direction` to `column` which is now makes the the **Main-axis** in Y-direction, column direction and the **Cross-axis** along the X-direction basically flipping it.

```css
 section.color{
display:flex; 
flex-direction: column;  /* This is what changed */
background-color: aquamarine;   
margin-top: 20px;        
}
```
<figure markdown style="width: 400px">
![alt text](<img/Screenshot 2024-11-03 162617.png>)
</figure>

### Flex Basis

So if we set thing like the `flex-basic` it is basically setting the width (or height) of each flexbox container item and it does so along the `Main-axis` so depending on weather the `flex-direction` is `row or column`, it will expand them in their respective direction. In other word, **we are flexing along the Main Axis**

```css
 section.color{
display:flex; 
/* flex-direction: column; */
background-color: aquamarine;          
}
section.color > div{
    flex-basis: 100px;
}
```


![alt text](img/image-46.png)


```css
 section.color{
display:flex; 
flex-direction: column;
background-color: aquamarine;          
}
section.color > div{
    flex-basis: 100px;
}
```
<figure markdown style="width: 400px">
![alt text](img/image-47.png)
</figure>

### Flex order

Flex order basically re-order the item in your flexbox, by stacking the highest
order item at the far end of the items. All items has a defaults 
`order: 0` if you  set an item order higher than 0, it stacks it to the far left.

!!! Note
    - This is an **ITEM property**
    - It operates along the **MAIN-AXIS direction**

Example:

<div class="grid" markdown>

```css
.box .green{
background-color: #00ff7b;
/* order:1; */
}
```

<figure markdown>
![alt text](img/image-48.png)
</figure>


```css
.box .green{
background-color: #00ff7b;
order:1;
}
```

<figure markdown>
![alt text](img/image-49.png)
</figure>

</div>

Just as the order can be set to positive values, It can also be set to negative values.


<div class="grid" markdown>

```css
.box .img{width: 100%;
max-width: 200px;
order: -1;
 }

```

![alt text](img/image-50.png)

</div>

The higher the order number, the higher the stacking

```css
.box .img{width: 100%;
max-width: 200px;
order: -2;
}
.box .green{
background-color: #00ff7b;
order:1;
}
.box .orange{
background-color: orange;
order:3;
}
```
![alt text](img/image-51.png)

## Flex Wrap

This is useful when the container items exceed what the window can container. E.g. In case
of say mobile devices with low screen dimension.

By default, the `flex-wrap` property is set to `nowrap`. 

!!! Note
    - This is a **COINTAINER/PARENT property**
    - It works along the **MAIN-AXIS**

```css
.box{
display: flex;

flex-direction: row;
flex-wrap: wrap;

/* Short-hand form */
flex-flow: row wrap;

}
```

On a wide screen
![alt text](img/image-53.png)

On a low dimension screen
<figure markdown="span" style="width: 500px">
![alt text](img/image-52.png)
</figure>

there is also a property called `wrap-reverse` which layout the items from the bottom up.

<figure markdown style="width:500px">
![alt text](img/image-54.png)
</figure>

### important Note
Depending on how the content is written flex wrap may work differently.

Look at this Example

This is the default  `nowrap` for this flex box:

<figure markdown style="width:400px">
![alt text](img/image-55.png)
</figure>

The moment it changes to `wrap` it behaves differently:
The expectation might be that I will still layout in a column along the row.

<figure markdown style="width:400px">
![alt text](img/image-56.png)
</figure>

The problem stems from the fact that the content is written in **one line**.
To make this behave in a more desirable way, one will need to break the text content in a more
manageable lines using the `br` tag. Rather than it being one line. 

<figure markdown style="width:400px">
![alt text](img/image-57.png)
</figure>

However, breaking using `br` tag diffinitely work, but the best solution method will be
to use the `@media` query to change the flex from `nowrap` to `wrap` after a certain width condition.

```css
 .container {
display: flex;
flex-wrap: nowrap;
}


@media screen and (max-width: 800px) {
.container{
    flex-wrap: wrap;
}
}
```
<div class="grid" markdown>

<figure markdown>
width `> 800px`
![alt text](img/image-58.png)
</figure>

<figure markdown style="width:250px">
width `< 800px`
![alt text](img/image-59.png)
</figure>
</div>