
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

## Computed Properties example 1

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

<figure markdown='span'>
  ![alt text](img/image-2.png)
</figure>


## Computed Properties Example 2

```js
import { ref, computed } from 'vue'
import socksGreenImage from './assets/images/socks_green.jpeg'
import socksBlueImage from './assets/images/socks_blue.jpeg'


// Selected 
const selVariant = ref(0)
  
const details = ref(['50% cotton', '30% wool', '20% polyester'])

const variants = ref([
  { id: 2234, color: 'green', image: socksGreenImage, quantity: 50 },
  { id: 2235, color: 'blue', image: socksBlueImage, quantity: 0 },
])

...

const image = computed(()=> variants.value[selVariant.value].image)
const inStock = computed(()=> variants.value[selVariant.value].quantity > 0)


// Updates index value when Hover
const updateVariant = (index) => {
  selVariant.value = index
 }
```

```html
<div class="product-container">
      <div class="product-image">    
        <img :src="image">
      </div>
      <div class="product-info">
        <!-- <h1>{{ title}}</h1> -->
        <h1>{{ updateTitle}}</h1>
        <p v-if="inStock">In Stock</p>
        <p v-else>Out of Stock</p>
        <ul>
          <li v-for="detail in details">{{ detail }}</li>
        </ul>
        <div v-for="(variant, idx) in variants" 
          key="variant.key"
          @mouseover="updateVariant(idx)"
          class="color-circle"
          :style="{ backgroundColor: variant.color }"
        >
        </div>
        <button
          class="button" 
          :class="{ disabledButton: !inStock }"
          :disabled="!inStock"
          v-on:click="addToCart"
        >
          Add to cart
        </button>
```


<figure markdown='span'>
![alt text](img/Computed_properties_demo.gif)
</figure>


## components and Props

```html title="App.vue"
<script setup>
import { ref} from 'vue'
import ProductDisplay from '@/components/ProductDisplay.vue'
const cart = ref(0)
const premiumData = ref(0)
const productDetails = ref([
  {name: "LongSocks", desc: "The best in town ", date: "23-05"},
  {name: "NothingSocks", desc: "Theirs nothing like it ", date: "11-07"},
  {name: "SnowSocks", desc: "Going for a snowy day", date: "02-08"},
])

</script>
  
<template>
  <div class="nav-bar">
    <div class="cart">Cart({{ cart }})</div>
  </div>
<ProductDisplay 
  :premiumUser ="premiumData" 
  :details="productDetails[0]" ></ProductDisplay>

<ProductDisplay 
  :premiumUser = "true"
  :details="productDetails[1]" ></ProductDisplay>

  <ProductDisplay premiumUser = "Omololu"
  :details="productDetails[2]" ></ProductDisplay>
  
</template>
```

Everything from the previous code applys here,
Think of it like a function but for frontEnd user.

We `props` are like the **parameters** and when we call the
`<ProductDetail>`, we pass the arguments *prop* to it.

```html title="ProductDisplay.vue"
<script setup>
import { ref, computed } from 'vue'
import socksGreenImage from '@/assets/images/socks_green.jpeg'
import socksBlueImage from '@/assets/images/socks_blue.jpeg'

const props = defineProps({
  "premiumUser": {type: Boolean, required: true},
  "details": {type: Object, required: true}
})


const product = ref('Socks')
const brand = ref('Vue Mastery')
const selectedVariant = ref(0)
const details = ref(['50% cotton', '30% wool', '20% polyester'])

const variants = ref([
  { id: 2234, color: 'green', image: socksGreenImage, quantity: 50 },
  { id: 2235, color: 'blue', image: socksBlueImage, quantity: 0 },
])

const title = computed(() => brand.value + ' ' + product.value)
const image = computed(() =>  variants.value[selectedVariant.value].image)
const inStock = computed(() =>  variants.value[selectedVariant.value].quantity > 0)
const shippingValue = computed(() => {
  if(props.premiumUser) return 'Free'
  else                  return '$2.99'
})
const productDetailInfo = computed(()=>return `${props.details.name}, ${props.details.desc},
  ${props.details.date}`)

const addToCart = () => cart.value += 1
const updateVariant = (index) => selectedVariant.value = index


</script>

<template>
      <div class="product-display">
    <div class="product-container">
      <div class="product-image">    
        <img v-bind:src="image">
      </div>
      <div class="product-info">
        <h1>{{ title }}</h1>
        <p v-if="inStock">In Stock</p>
        <p v-else>Out of Stock</p>
        <p>shipping : {{ shippingValue }}</p>
        <p>{{productDetailInfo}}</p>
        <ul>
          <li v-for="detail in details">{{ detail }}</li>
        </ul>
        <div 
          v-for="(variant, index) in variants" 
          :key="variant.id"
          @mouseover="updateVariant(index)"
          class="color-circle"
          :style="{ backgroundColor: variant.color }"
        >
        </div>
        <button
          class="button" 
          :class="{ disabledButton: !inStock }"
          :disabled="!inStock"
          v-on:click="addToCart"
        >
          Add to cart
        </button>
      </div>
    </div>
  </div>
</template>

```
