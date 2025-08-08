# Working with JS Promise


## Example loading File Content

```html title="helloFile.html"
<div>
    <h1>Header 1</h1>
    <h2>Header 2</h2>
    <h3>Header 3</h3>
    <h4>header 4</h4>
</div>
```

```html title="index.html"
<!DOCTYPE html>
<html>
...
  
    <body style="background-color: #333; color:#ddd">

        <h1>Testing out Promises</h1>
        <div id="demo"></div>

        <script>
            async function GetFile(filename){
                let filePromise = new Promise((resolve) => {
                    let req = new XMLHttpRequest()
                    req.open('GET', filename)
                    req.onload = ()=>{
                        if(req.status == 200) 
                            resolve(req.response)
                        else                 
                            resolve("file not found")
                    }
                    req.send()
                })
    
                // load the request data
                document.getElementById("demo").innerText = await filePromise
                console.log(filePromise)
            }
    
            GetFile("./helloFile.html")
        </script>
    </body>
</html>
```

<figure markdown='span'>
    ![alt text](img/image-12.png)
</figure>

### Improved version example on Promises

```js title="index.js"
export async function GetFile(filename){
    let filePromise = new Promise((resolve) => {
        let req = new XMLHttpRequest()
        req.open('GET', filename)
        req.onload = ()=>{
            if(req.status == 200) 
                resolve(req.response)
            else                 
                resolve("file not found")
        }
        req.send()
    })

    // load the request data
    const section =  document.createElement('section')
    document.getElementById("demo").appendChild(section)
    section.innerHTML = await filePromise
}

export async function someFun01(){
    console.log("Hello From SomeFun 01")
    let someFunPromise = new Promise((resolve)=>{
        setTimeout(()=>{resolve(
            `<p style='color: greenyellow'>Finished Counting
             <span style="font-size:30px; color: pink !important; "> YEEEAAAHHH </span> </p>`
            )}, 3000)
    })

   
    const countNode = document.createElement('div')
    countNode.innerHTML = "<p style ='color: yellow'> waiting for <code>SetTimeout</code></p>"
    document.getElementById("demo").appendChild(countNode)
    countNode.innerHTML = await someFunPromise
}

```

```js title="index.js"
import {GetFile, someFun01} from './utility.js'

GetFile("./helloFile.html")
someFun01()
```
<figure markdown='span'>
![alt text](img/promisesTest.gif)
</figure>
