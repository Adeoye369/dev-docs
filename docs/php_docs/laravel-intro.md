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

- It will create `HomeController.php` class in the *App/Http/Controller* directory in your project folder.

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

All vue views and located in *Resources/js/pages* inside here we will create a *User*  folder for handling the basic views

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
![alt text](<Screenshot 2026-08-21 043800.png>)