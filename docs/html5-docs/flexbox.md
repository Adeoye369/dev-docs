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