
# introduction to Vue

Getting started

- `npm create vue@latest`
- Set your project name
- Just press enter for the remaining options
Once all the necessary installations is done

Do the following:

```bash
cd <new_project_name>
npm install
npm run dev
```



<figure markdown='span'>
<figcaption> Then you will get a localhost Address </figcaption>
  ![cmd vite local host](img/image.png){width="70%"}
</figure>


<figure markdown='span'>
    <figcaption> Click on the localhost, you will have a default view of vue </figcaption>
    ![Default vuepage for vuew](img/image-1.png)
</figure>

## Computed function example

```js
import { ref, computed } from 'vue'

const product = ref('Socks')
const brand = ref('Vue Mastery')
const newTitle = ref('')


// Methods 
const title = computed(()=>{
  return brand.value + " " + product.value
})

const updateTitle = computed(()=>{
  // return default
  if (newTitle.value.length === 0) return title.value
  // trucate if too long
  else if(newTitle.value.length > 15) return newTitle.value.slice(0, 15) + " ... "
  // return length of string
  else return newTitle.value
})
```

```html
  ...
  <h1>{{ updateTitle}}</h1>
  ...
  ...
  ...
  
  <form @submit.prevent="updateTitle">
          <input type="text" placeholder="Write New Title..." v-model="newTitle"/>
          <!-- <button type="submit" >set name</button> -->
        </form>
```
