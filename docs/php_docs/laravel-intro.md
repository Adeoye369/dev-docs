# Getting Started with Laravel

## Downloading 

- Downloading using Command from [Laravel Website](https://laravel.com/docs/13.x/installation)

```cmd
# Run as administrator...
Set-ExecutionPolicy Bypass -Scope Process -Force; 
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; 
iex ((New-Object System.Net.WebClient).DownloadString('https://php.new/install/windows/8.5'))
```

- Place the `herd-lite/bin` directory in the "C drive" (⚠️Personal Preference)

- Edit the Environment Variable (Win+R > `sysdm.cpl`) to accommodate the changes by adding `C:\herd-lite\bin` to System Wide PATH variable.

- Run `composer global require laravel/installer` to install laravel


## Getting Started with Basics

- create initial boilerplate code with:
    `laravel new "laravelApp04-vue"`
- wait for it to download all necessary files, and answer all the questions for Boost Ai Setup


## First Laravel Project

### Creating Controller Class & Methods
 - First create a new Controller - Here is what hold functions (Actions) that connects both the **View(Vue in our case)** and the **Router** use the `php artisan make:controller <ControllerClassName>`  in our case, we will make `HomeController`

- It will create `HomeController.php` class in the *App/Http/Controllers* directory in your project folder.

```php title="HomeController.php"
<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Inertia\Inertia;

class HomeController extends Controller
{
    // functions called by Router
    public function homeFunc(){
        return Inertia::render("User/Index", [
            'homeTitle' => "Title home"
        ]);
    }
    
    public function userFunc($userInfo, $age){
        return Inertia::render("User/UserDetail", [
            'userInfo' => $userInfo,
            'age' => $age
        ]);
    }
}

```

### Creating the Vue Files

All vue views are located in *Resources/js/pages* inside here we will create  a *User*  folder for handling the basic views, Then create `Index.vue` file inside it

```vue title="Index.vue"
<script setup>
import {Head} from '@inertiajs/vue3'

</script>
<template>
    <Head title="Our Hommer Page"/>
    <div>
        <h1>Hello Home Page</h1>
    </div>
</template>
```

```vue title="UserDetail.vue"
<script setup>
defineProps({
    userInfo: String,
    age: Number
})
</script>
<template>
    <div>
        <h1>User Detail</h1>
        <p>{{ userInfo }}</p>
        <p><span>Age:</span> {{ age }}</p>
    </div>
</template>
```

### Final Process Creating the Route

inside the *routes\web.php* which is one of the default files, we create the following functions

```php title="web.php"
Route::get("/", [HomeController::class, 'homeFunc']);
Route::get("/user/{userInfo}/{age}", [HomeController::class, 'userFunc']);
```

with all the functions intact, we run in the powershell

```bash
 composer run dev
```
![Finished Sample](<img/Screenshot 2026-08-21 043800.png>)


## Using Default Layout

Create a new vue template that say `BaseLayout.vue`

```vue title="BaseLayout.vue"

<script setup>
import { ref } from 'vue';
import { Link } from '@inertiajs/vue3';
 const timer = ref(0);
setInterval(()=>{timer.value++}, 1000)
</script>
<template>
    <div class="flex flex-col  min-h-screen w-full">
        <main class="bg-blue-500 flex flex-col justify-center items-center grow">
            <!-- Where the content will goto -->
            <slot></slot> 
        </main>
        <footer 
            class="h-10 bg-gray-400 w-full flex justify-center" >
                <h3>Footer ©️{{ new Date().getFullYear() }}</h3>
        </footer>
    </div>
</template>
 
```

Then import it into the vue file that will make use of it


```vue title="BaseLayout.vue"
<script>
import Layout from "./components/BaseLayout.vue";
defineOptions({layout: BaseLayout});
</script>

<template>
<!-- Content here goes into Layout Slot -->
</template>

```

### Using Global Default Layout

Go to your `App.ts or .js`  add the following hilighted codes

```ts hl_lines="2 12"
import { createInertiaApp } from '@inertiajs/vue3';
import Layout from './pages/components/MainLayout.vue';

const appName = import.meta.env.VITE_APP_NAME || 'Laravel';

createInertiaApp({
    title: (title) => (title ? `${title} - ${appName}` : appName),
    progress: {
        color: '#4B5563',
    },

    layout: ()=> MainLayout
});
```

!!! note
    If another layout is imported in a specific vue template, **it will override the global Default layout**

## Installing laravel debugbar

### Debugbar
Run `composer require --dev barryvdh/laravel-debugbar `

### Ide helper
Run `composer require --dev barryvdh/laravel-ide-helper`

## Working With Database

```bash
php artisan make:controller <ControllerName>
```

If you would like to generate a database migration when you generate the model, 
you may use the `--migration` or `-m` option:
```bash
php artisan make:model <ModelName> 
php artisan make:model <ModelName> --migration
```

```bash
# Generate a model and a FlightFactory class...
php artisan make:model Flight --factory
php artisan make:model Flight -f

# Generate a model and a FlightSeeder class...
php artisan make:model Flight --seed
php artisan make:model Flight -s

# Generate a model and a FlightController class...
php artisan make:model Flight --controller
php artisan make:model Flight -c

# Generate a model, FlightController resource class, and form request classes...
php artisan make:model Flight --controller --resource --requests
php artisan make:model Flight -crR

# Generate a model and a FlightPolicy class...
php artisan make:model Flight --policy

# Generate a model and a migration, factory, seeder, and controller...
php artisan make:model Flight -mfsc

# Shortcut to generate a model, migration, factory, seeder, policy, controller, and form requests...
php artisan make:model Flight --all
php artisan make:model Flight -a

# Generate a pivot model...
php artisan make:model Member --pivot
php artisan make:model Member -p
```


```bash
php artisan migrate
php artisan migrate:rollback

# ⚠️NERVER USE IN PRODUCTION - REFRESH DESTROYS DATA
php artisan migrate:refresh 
php artisan migrate:refresh --seed

```

```bash
php artisan make:factory ListingFactory
php artisan make:factory ProductFactory 

php artisan db:seed
```