# Introduction to HTML and CSS

<div class="grid" markdown>
<figure markdown="span"  style="width:200px">
![alt text](img/image.png)
</figure>
```css
font-family: 'Montserrat', sans-serif;
```
</div>

<div class="grid" markdown>
<figure markdown="span"  style="width:300px">
![alt text](img/image-2.png)
</figure>

```css
font-family: 'Merriweather', serif;
```
</div>

<div class="grid" markdown>
<figure markdown="span" style="width:400px">
![alt text](img/image-1.png)
</figure>

```css
font-family: 'Sacramento', cursive;
```
</div>

!!! note
    Note that this are all [google fonts](https://fonts.google.com/) and you will need to include the link below in your head tag:
    ```html
    <link href="https://fonts.googleapis.com/css?family=Merriweather|Montserrat|Sacramento" rel="stylesheet">
    ```


## Basic Example Css

<figure markdown="span" style ="width:400px">
![alt text](img/image-3.png) 
</figure>

```css
.container{
    /* position: relative; */
    margin: auto 100px;
    background-color: bisque;
    height: 50vh;
}

.container h1{
    text-align: center;
    font-family: 'Montserrat', serif;;
}
```

### Control the font with `font-size`

<div class="grid" markdown>

```css
 body {
     font-size: 14px; 
     }
```

<figure markdown="span">
![alt text](img/image-4.png)
</figure>
</div>

### affect weigth with `font-weight`

<div class='grid' markdown>

```css
body {
    font-weight: bold;
    }
```


![alt text](img/image-5.png)


</div>


<div class='grid' markdown>
</div>


### Style your text more with `text-decoration`

<div class='grid' markdown>

```css
body {
 text-decoration: underline;
 }
```


![alt text](img/image-6.png)

</div>

### More styling wiht `font-style`

<div class="grid" markdown>

```css
font-style: italic;
```

![alt text](img/image-15.png)

</div>

## Working with font-family

#### serif

<div class='grid' markdown>

Serif are words that has sharp, edges - This fonts are similar to the newspaper fonts.
   Examples - `Times, Times New Roman, Georgia, Savannah, Palomino, Quarter`

![alt text](img/image-8.png)
</div>


#### san-serif
<div class='grid' markdown>

The word "San" is a french word meaning "without". This has no serif basicly, no sharp edges
Examples `Verdana, Geneva, Arial, Arial Black, Trebuchet MS, Iceland, Angel, Nautica`

![alt text](img/image-9.png)
</div>

#### Monospace
<div class='grid' markdown>

This are fonts that has constant width characters. Eg. horizontal space in "i" take same as in "w". The are primary used for codes too.
Examples `Courier, Courier New, Andele Mono, Messenger, Bainbridge`

![alt text](img/image-10.png)

</div>

#### Cursive
<div class='grid' markdown>

This are font that looks like handwritten. This fonts are sometimes used in headings.
Examples `Comic Sans, Apple Chancery, Cartoon`

![alt text](img/image-11.png)

</div>

#### Fantasy Family

<div class='grid' markdown>

This are fancy and fantansy styled fonts
Examples - `Last Ninja, Impact, Crush`

![alt text](img/image-12.png)
</div>

### Using Font family

Most of the time when specifying font family, you make looks like so:

```css
/* Suggetst options to fallback to */
 font-family: Verdana, Geneva, Arial, sans-serif; 

 /* one prefers */
 font-family: Verdana, sans-serif;

/* Use the default font family from device */
 font-family:  sans-serif;
```

### Changing Font size

![alt text](img/image-13.png)
Picture from **Head First Html and Css**

The 3 major font-changing css are:
`px`,`em` and `%`

```css
body { font-size: 15px; } /* Using the screen pixel */
 h1 { font-size: 2em; } /* 2 the size of parent size */
 h2 { font-size: 150%; } /* 150% of the parent size  */
 h3{font-size: large} /* or small */

```

![alt text](img/image-14.png)