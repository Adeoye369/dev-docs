# Basic Setup for Vue Express

First create a `server` and `client` folder to hold the different respective codes

## Create Express Backend

Navigate to your server folder to initialize Node.js and install Express.

- Initialize: Run `npm init -y` inside the server directory.(Get Package install)
- Install Express: Use `npm install express`.
  - other packages needed : `nodemon`(node monitor), `cors`(Cross-Origin Resources Sharing)
Create Server File: Create `main.js` and add a basic route javascript

In your server side package manager, remember to:

- Change js type from commonjs to module `"type":"module"`
- Add `"start":"nodemon main.js"` under the `test` categories 


```js
import express from "express"

const SERVER_PORT = process.env.port || 3000
const app = express()
// app.use(cors())
// app.use(express.json())

app.get('/api/hello', (req, res)=>{
 res.json({hello: "Server says Hello"})

app.listen(SERVER_PORT, ()=>console.log(`running Server on port ${SERVER_PORT}`))

```

Run `npm start` nodemon will start the server.

## Create Vue Frontend

Navigate to your client folder and scaffold a new Vue project using the `official Vue starter.`

Generate Project: In your root folder, Run `npm create vue@latest ` and follow the prompts.

<figure markdown='span'>
    ![alt text](img/image-12.png)
    <figcaption>Use your client folder as project name </figcaption>
</figure>

Install Dependencies: Run `npm install` to install dependencies
cd into your `client` folder and Run the boilerplate: `npm run dev`

You should basic Vue running on `localhost:5173`
<figure markdown='span'>
    ![alt text](img/image-13.png)
    <figcaption> basic Vue Page </figcaption>
</figure>

Directory setup
<figure markdown='span'>
    ![alt text](img/image-14.png)
</figure>

## Connecting your Server to Client

- Install `Axios` for fetch data
- In your server make sure you have `cors` activated in your express

```js title="server/main.js" hl_lines="2 6"
import express from "express"
import cors from "cors"

const SERVER_PORT = process.env.port || 3000
const app = express()
app.use(cors())
app.use(express.json())

app.get('/api/hello', (req, res)=>{
 res.json({hello: "Server says Hello"})
})

```

in your client side.

```js title="client/src/main.js"

import { createApp } from 'vue'
import App from './App.vue'

const app = createApp(App)
app.mount('#app')

```

in your `App.vue`

```html title="App.vue"
<script setup>
import { onMounted,ref } from 'vue';
import axios from 'axios';


const SERVER_BASE_URL = "http://localhost:3000"
const hello_msg = ref('')

onMounted(async ()=>{
  const res = await axios.get(`${SERVER_BASE_URL}/api/hello`)
  hello_msg.value  = res.data.hello
})

</script>

<template>
  <h1>{{hello_msg}}</h1>
  <p>
    Visit <a href="https://vuejs.org/" target="_blank" rel="noopener">vuejs.org</a> to read the
    documentation
  </p>
</template>

<style scoped></style>

```

## Proxy for CORS localhost

In Vite, you can configure a dev server proxy in your `vite.config.js (or .ts)` file. This intercepts requests starting with a specific prefix (like /api) and forwards them to your Express server, making the browser think the request is coming from the same origin as your frontend.

1. Update vite.config.js

Add the server.proxy configuration to your Vite file:

```js title="vite.config.js"

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

export default defineConfig({
  plugins: [vue()],
  server: {
    proxy: {
      // Any request starting with /api will be proxied
      '/api': {
        target: 'http://localhost:3000', // Your Express server address
        changeOrigin: true,             // Recommended for CORS
        // Use rewrite if your Express routes DON'T start with /api
        // rewrite: (path) => path.replace(/^\/api/, '') 
      }
    }
  }
})
```

2. Update your API calls in Vue

Instead of using the full URL `(e.g., http://localhost:3000/api/users)`, use a relative path. Vite will automatically prepend the proxy target. 

javascript
```js 
// Inside a Vue component or Axios setup
import axios from 'axios';

// This is automatically proxied to http://localhost:3000/api/users
const response = await axios.get('/api/users');

```

### Our final Script code could look like so

```html title="src/App.vue" hl_lines="5"
<script setup>
...

onMounted(async ()=>{
  const res = await axios.get('/api/hello')
  hello_msg.value  = res.data.hello
})
...
</script>

```

## Loading , Reloading

### 1. The "Vue Way": Refresh the Data (Recommended)

Instead of reloading the page, simply call your data-fetching function again. This is faster and smoother for the user.

```js
const products = ref([]);

const fetchCart = async () => {
  const response = await axios.get('/api/cart');
  products.value = response.data;
};

const addToCart = async (id) => {
  const res = await axios.post('/api/cart', { productId: id });
  if (res.status === 200) {
    // Just refresh the list, don't reload the page!
    await fetchCart(); 
  }
};
```

### 2. The "Hard" Reload (F5 Style)

If you absolutely must reload the entire browser window (e.g., to reset a complex global state or legacy reasons), use the standard Web API Location: reload() method:

```js
const createOrder = async () => {
  const res = await axios.post('/create-order');
  if (res.status === 200) {
    window.location.reload();
  }
};

```

## URL States

| URL State	| route.query.edit	| !!route.query.edit	| Result
|-----------|-------------------|--------------------|----------
|`?edit=true` | 	`"true"` | 	`true`	 | **Edit Mode**
| ?edit=1	| `"1"` |	`true` | 	**Edit Mode**
|(No query) | 	`undefined` |	`false` | 	**Add Mode**
| `?edit=`	| `""`	| `false` | 	**Add Mode**


## The "Key-Changing" Technique (Best for Full Resets)
By adding a :key to your <router-view> (usually in App.vue), 
you force Vue to destroy the old component and create a brand new one every time the URL changes. 
This automatically resets all ref and reactive form data to their initial values.

```html
<!-- In App.vue -->
<router-view :key="$route.fullPath"></router-view>
<!-- OR -->
<RouterView :key="$route.fullPath"/>
```

## Difference between `useRoute()` and `useRouter()` in vue

In Vue Router (Composition API), the difference is simple: 
one is for **"reading"** and the other is for **"doing."**

### 1. useRoute (The "Reader")

Use this when you need to look at information about the current page. 
It returns a reactive object containing the URL details.
What you get: `path`, `params`, `query`, `hash`, and `name`.

Common Use Case: Getting an ID from the URL or checking for an `edit=true` query.

```js
import { useRoute } from 'vue-router';
const route = useRoute();

console.log(route.params.id); // "123"
console.log(route.query.edit); // "true"
```


### 2. useRouter (The "Doer")

Use this when you want to change the page or move the user somewhere else. 
It represents the router "engine."
What you get: Methods like `push()`, `replace()`, `go()`, and `back()`.
Common Use Case: Redirecting to a "Success" page after a form submission.

```js
import { useRouter } from 'vue-router';
const router = useRouter();

const goToHome = () => {
  router.push('/home'); // Moves the user to the home page
};
```


### Comparison Table

| **Feature** |`useRoute` |`useRouter`
|----------|-----------|---------------|
| **Purpose** |Information about the **Current Route** | The **Router Instance** itself
| Think of it as... | **A Map** (shows where you are) | **The Driver** (takes you somewhere)
| Key Properties | `params`, `query`, `path` | `push()`, `replace()`, `resolve()`
| Reactivity | **Yes** (updates when URL changes) | **No** (the methods stay the same)


Pro-tip: If you are in a watcher, you'll likely watch `route.path `to trigger logic when the user moves, 
and then use `router.push() `to redirect them if needed.

##  Using Dynamic Params (Clean URL)

If your error route is defined with a dynamic segment like path: `'/error/:code'`, 
you can pass the code as a param.

```js
// Route: { path: '/server-error/:code', name: 'Error' }
router.push({ 
  name: 'Error', 
  params: { code: 500 } 
});
```

## use case for defineProps and defineEmits

Here we use `props = defineProps({productId ...})` props to pass the id to the component. 
Then we use `emits = defineEmits(['refresh'])` to tell the parent page to refresh the page
when it has successfully delete the product

```html title="DeleteProductBtn.vue"
<script setup>
import axios from 'axios';

const props = defineProps({
    productId: Number
})

const emits = defineEmits(['refresh'])

// Delete Action 
const deleteProduct = async (productID) => {
  if (!confirm('Are you sure you want to delete this?')) return;
  try {
      const res = await axios.post("/api/admin/delete-product", {productId : productID})
      console.log(res.data)

      // Reload page on success
      if(res.status === 200)
          // Refresh the page to load update the list
          emits('refresh')

  } catch (error) {
      console.error(error)  
  }

}
</script>

<template>
    <button class="btn" @click="deleteProduct(productId)"> Delete </button>
</template>
```

In the parent vue file here is how it looks

```html
<script setup>
// Get the Products from the Admin server
async function getAdminProducts(){
...
}


onMounted( ()=>{
    getAdminProducts()
})

</script>
<template>

    <main>
        <div class="main-content__desc" v-if="hasProducts">
        
            <h1>Admin - Products</h1>
            <!-- <p>List of all the products...</p> -->
            <div class="grid">
              <article class="card product-item" v-for="product in prods">
            ...
                                
                         <DeleteProductBtn :productId ="product.id" @refresh="getAdminProducts" />
                    </div>
              </article>
```
## [BASIC] Pagination with Node Express Vue 

```js
// GET /api/products?page=1&limit=10
router.get('/products', async (req, res) => {
  const page = parseInt(req.query.page) || 1;
  const limit = parseInt(req.query.limit) || 10;
  const offset = (page - 1) * limit;

  try {
    // findAndCountAll returns the total rows matching the condition AND the data
    const data = await Product.findAndCountAll({
      limit: limit,
      offset: offset,
      order: [['createdAt', 'DESC']] // Newest products first
    });

    const totalPages = Math.ceil(data.count / limit);
    
    res.json({
      totalItems: data.count,
      totalPages: totalPages,
      currentPage: page,
      products: data.rows
    });
  } catch (error) {
    res.status(500).json({ message: "Error retrieving products" });
  }
});

```

```html
<template>
  <div>
    <!-- Product List -->
    <div v-for="product in products" :key="product.id">
      <h3>{{ product.name }}</h3>
    </div>

    <!-- Pagination Controls -->
    <div class="pagination">
      <button :disabled="currentPage === 1" @click="fetchProducts(currentPage - 1)">
        Previous
      </button>

      <span>Page {{ currentPage }} of {{ totalPages }}</span>

      <button :disabled="currentPage === totalPages" @click="fetchProducts(currentPage + 1)">
        Next
      </button>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue';
import axios from 'axios';

const products = ref([]);
const currentPage = ref(1);
const totalPages = ref(1);
const limit = 10;

const fetchProducts = async (page = 1) => {
  try {
    const response = await axios.get(`/api/products?page=${page}&limit=${limit}`);
    products.value = response.data.products;
    currentPage.value = response.data.currentPage;
    totalPages.value = response.data.totalPages;
  } catch (error) {
    console.error("Error fetching products:", error);
  }
};

onMounted(() => {
  fetchProducts(currentPage.value);
});
</script>

```

## [ADVANCE] Pagination with Node Express(BackEnd) and Vuejs (FrontEnd)

```js

// ROUTE
shopRouter.get('/products', shop.getShopProducts)

. . .
// CONTROLLER
// Updated getShopProducts Controller
export const getShopProducts = async (req, res) => {
    try {

        // Extract and parse pagination parameters from the query string
        const page = parseInt(req.query.page) 
        const pageSize = parseInt(req.query.pageSize) 
        const offset = (page - 1) * pageSize;

        const {count, rows} = await Product.findAndCountAll(
            {
                limit: pageSize,
                offset: offset,
                order: [['createdAt', 'DESC']], // Optional: Keeps order consistent across pages
            
                // Tells Sequelize to fetch related User data
                include: [{
                    model: User, 
                    attributes: ['name', 'email'] // Only pull the fields you need
                    }]
             }
        );

        // Map through products to move User fields to the top level
        const flattenedProducts =  flattenProducts(rows)

        res.json({
            prods: flattenedProducts,
            hasProducts: flattenedProducts.length > 0,
            currentPage: page,
            totalItems: count,
            totalPages: Math.ceil(count / pageSize),
        });
    } catch (err) {
        res.status(500).json({ message: "Error fetching products" });
    }
};

```

```html
<script setup>
import ...;




// Reactive state to hold your data
const prods = ref([]);

const hasProducts = ref(false);
const isLoading = ref(true);

// Reactive State Variables
const currentPage = ref(1);
const totalPages = ref(1);
const totalItems = ref(0)
const pageSize = 3;
const BUTTON_RANGE = 2




// Computed Property for dynamic button range (-2 and +2)
const visiblePages = computed(() => {
  const current = currentPage.value;
  const max = totalPages.value;
  
  let start = Math.max(1, current - BUTTON_RANGE);
  let end = Math.min(max, current + BUTTON_RANGE);

  const pages = [];
  for (let i = start; i <= end; i++) {
    pages.push(i);
  }
  return pages;
});

const fetchProducts = async (pageNumber) => {

  if (pageNumber < 1 || pageNumber > totalPages.value) return;
  try {
    // Replace with your actual backend URL
    const response = await axios.get('/api/products', 
      {
        params: {
          page: pageNumber,
          pageSize: pageSize
        }
      }
    )
    prods.value = response.data.prods;
    hasProducts.value = response.data.hasProducts;
    currentPage.value = response.data.currentPage;
    totalItems.value = response.data.totalItems
    totalPages.value = response.data.totalPages;
  } catch (error) {
    console.error("Error loading products:", error.response.data);
  } finally {
    isLoading.value = false;
  }
};

onMounted(() => {
  authStore.initAuth()
  fetchProducts(1);
});



</script>

<template>
  <main>
    <div class="main-content__desc">
      
      <template v-if="hasProducts" style="position: relative">
        <!-- Good: Will safely wait until user object is populated -->
      <h2 v-if="authStore.user">Welcome, {{ authStore.user?.name || authStore.user.email }}</h2>
        <h2 v-else >Welcome to Productsy!</h2>
        
        <h4 style="position: absolute; right: 10px">
          total Items: <span>{{ totalItems }}</span>
        </h4>
        <div class="grid">
          
          
          <ProductView v-for="product in prods" 
          :key="product.id" 
          :product = product 
          :isAdmin="false"/>

        </div>

        <!-- Advanced Pagination Controls -->
    <div class="pagination-controls" v-if="totalPages > 1">
      
      <!-- First Page Button -->
      <button v-if="!visiblePages.includes(1)"
        @click="fetchProducts(1)" 
        :class="{ active: currentPage === 1 }"
      >
        <<
      </button>

      <!-- Dynamic Page Numbers -->
      <button 
        v-for="page in visiblePages" 
        :key="page" 
        @click="fetchProducts(page)"
        :class="{ active: currentPage === page }"
      >
        {{ page }}
      </button>

      <!-- Last Page Button -->
      <button v-if="!visiblePages.includes(totalPages)"
        @click="fetchProducts(totalPages)" 
        :class="{ active: currentPage === totalPages }"
      >
        >> ({{ totalPages }})
      </button>

    </div>

      </template>

      <!-- Logic: replaces <% } else { %> -->
      <template v-else>
        <h2>No Product in Cart</h2>
        <div>
          <button class="btn btn__add_item">
            <router-link to="/admin-add-product">Add Item</router-link>
          </button>
        </div>
      </template>
    </div>
  </main>

  <EndPage/>
</template>

<style scoped>
.pagination-controls {
  display: flex;
  justify-content: center;
  gap: 5px;
  margin-top: 20px;
}
button {
  padding: 8px 12px;
  cursor: pointer;
  border: 1px solid #ccc;
  background-color: #fff;
}
button.active {
  background-color: #42b983;
  color: white;
  border-color: #42b983;
  font-weight: bold;
}
button:disabled {
  cursor: not-allowed;
  opacity: 0.5;
}
</style>

```
