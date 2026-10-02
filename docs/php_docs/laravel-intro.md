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

### Vue Devtools 
Visit [Vue DevTool site](https://devtools.vuejs.org/getting-started/installation) you will see link that direct you to the appropriate site depending on your choice of browser. Here we are using [google chrome](https://chromewebstore.google.com/detail/vuejs-devtools/nhdogjmejiglipccpnnnanhbledajbpd?utm_source=ext_sidebar&pli=1). 

## Working With Database

```bash
php artisan make:controller <ControllerName>
```


## Connecting to Database

We will be running our database using Docker. Docker allows you to run software application in its own environment other than you local machine.
 1. first we create Docker compose file in our root:

    ```yml title="docker-compose.yml"
    services:
    mysql:
        image: mariadb:12.3.3
        container_name: laravel-mysql
        command: --default-authentication-plugin=mysql_native_password
        restart: unless-stopped
        environment:
        MYSQL_ROOT_PASSWORD: root
        # MYSQL_DATABASE: app
        # MYSQL_USER: app
        # MYSQL_PASSWORD: app
        ports:
        - "3306:3306"

    adminer:
        image: adminer
        container_name: laravel-adminer
        restart: unless-stopped
        ports:
        - "8080:8080"
        environment:
        ADMINER_DEFAULT_SERVER: mysql

    ```

    Here we will be installing `MariabDB` opensource version of mysql and `Adminer` for managing database

2.  Make sure docker desktop is running and then run `docker compose up`. If you are running it for the first time, docker will first download the application but once done you should be able to visit Adminer in your port `localhost:8080`

3.  Next configure the connection
    - Open the `.env` file 
    - go to the section that shows `DB_` set your **Database Name**, **Username** and **Password**
        ```bash
            DB_CONNECTION=mysql
            DB_HOST=127.0.0.1
            DB_PORT=3306
            DB_DATABASE=larabillydb
            DB_USERNAME=root
            DB_PASSWORD=root
        ```
    - Manually create the DB in the `Adminer` on port 8080.
        create new Database with collation name: "utf8mb4_general_ci" save the changes

    - Open  `/config/database.php` and fill in the DB info:
        ```php


        use Illuminate\Support\Str;
        use Pdo\Mysql;

        return [

            /*
            |--------------------------------------------------------------------------
            | Default Database Connection Name
            |--------------------------------------------------------------------------
            | Here you may specify which of the database connections below you wish
            | to use as your default connection for database operations. 
            */

            'default' => env('DB_CONNECTION', 'mysql'),

            /*
            |--------------------------------------------------------------------------
            | Database Connections
            |--------------------------------------------------------------------------
            | Below are all of the database connections defined for your application.
            | An example configuration is provided for each database system which
            | is supported by Laravel. 
            |
            */

            'connections' => [


                'mariadb' => [
                    'driver' => 'mariadb',
                    'url' => env('DB_URL'),
                    'host' => env('DB_HOST', '127.0.0.1'),
                    'port' => env('DB_PORT', '3306'),
                    'database' => env('DB_DATABASE', 'larabillydb'),
                    'username' => env('DB_USERNAME', 'root'),
                    'password' => env('DB_PASSWORD', 'root'),
                    'unix_socket' => env('DB_SOCKET', ''),
                    'charset' => env('DB_CHARSET', 'utf8mb4'),
                    'collation' => env('DB_COLLATION', 'utf8mb4_unicode_ci'),
                    'prefix' => '',
                    'prefix_indexes' => true,
                    'strict' => true,
                    'engine' => null,
                    'options' => extension_loaded('pdo_mysql') ? array_filter([
                        Mysql::ATTR_SSL_CA => env('MYSQL_ATTR_SSL_CA'),
                    ]) : [],
                ],

                // 'pgsql' => [
                // . . . Other DB Servers goes here

            ],


            'migrations' => [
                'table' => 'migrations',
                'update_date_on_publish' => true,
            ],
            
        ```

    - Run `php artisan db:show`


## Models and Migrations


If you would like to generate a database migration when you generate the model, 
you may use the `--migration` or `-m` option:
```sh
php artisan make:model <ModelName> 
php artisan make:model <ModelName> --migration

```

### Other Flag to create other Files
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

### Model example

We will be using 
```sh
# Example
php artisan make:model Transaction -m
```
for our example:
 In *App/Models* directory, a php file  `Transaction.php` file is created and
  in *database/migrations*, a php file with `<date_time_format>_create_transactions_table.php` file is created

  ```php title="Transaction.php"
    <?php

    namespace App\Models;

    use Illuminate\Database\Eloquent\Model;

    class Transaction extends Model
    {
        //
    }
  ```

  ```php title="<date_time_format>_create_transactions_table.php"
     <?php

        use Illuminate\Database\Migrations\Migration;
        use Illuminate\Database\Schema\Blueprint;
        use Illuminate\Support\Facades\Schema;

        return new class extends Migration{
            /** Run the migrations.*/
            public function up(): void 
            {
                Schema::create('transactions', function (Blueprint $table) {
                    $table->id();
                    $table->timestamps();
                });
            }

            /*** Reverse the migrations.*/
            public function down(): void 
            {
                Schema::dropIfExists('transactions');
            }
        };

  ```




### Migration and Adding Migration Manually

Modify the default Migration file before migrating it:

```php title="<...>_create_transaction_table.php"
 public function up(): void
    {
        Schema::create('transactions', function (Blueprint $table) {
            $table->id();
            $table->timestamps();
            $table->unsignedInteger('date');
            $table->string('category');
            $table->text('description');
            $table->decimal(10, 2);
        });
    }

...

```
To create it on the database, use `php artisan migrate`



```bash
php artisan migrate

# Check current status of migrate
php artisan migrate:status

# Goes a step back by calling the down() function
php artisan migrate:rollback 

# rolling back just a specific migration
php artisan migrate:rollback --path="database/migrations/xxxx_xx_xxx_xxx_add_fields_to_listings_table.php"

# ⚠️NERVER USE IN PRODUCTION - REFRESH, FRESH AND RESET DESTROYS DATA
php artisan migrate:refresh # rollback ALL and re-migrate 
php artisan migrate:refresh --seed

```
If you've already created your table but need to either add fields update field etc.
Use `php artisan make:migration 'action_on_the_table'`

```sh
php artisan make:migration add_fields_to_transactions_table --table="transactions"
php artisan make:migration change_bio_in_users_table --table="users"
```

```php
    <?php

    return new class extends Migration
    {
        /**
         * Run the migrations.
         */
        public function up(): void
        {
            Schema::table('transactions', function (Blueprint $table) {
                // change 'date' from integer to string
                $table->string('date')->nullable()->change();
            });
        }

        /**
         * Reverse the migrations.
         */
        public function down(): void
        {
            Schema::table('transactions', function (Blueprint $table) {
                //
            });
        }
    };

```



## Model Factories and Seeders

### Making Factories
This is filling the database table with fake generated data.

```sh
php artisan make:factory ListingFactory
php artisan make:factory ProductFactory 

```

In our case we will be using the **Transaction** model we created earlier:

```sh
php artisan make:factory TransactionFactory
```

It can be found in *database/factories* folder. 
You can use a what is called Faker to populate fake data into your database.


```php title="TransactionFactory.php"
<?php

namespace Database\Factories;

use App\Models\Transaction;
use Illuminate\Database\Eloquent\Factories\Factory;
/**
 * @extends Factory<Transaction>
 */
class TransactionFactory extends Factory
{
    /*** Define the model's default state.
     * @return array<string, mixed> */

    public function definition(): array
    {
       return [
            'date' => fake()->date('d-m-y'), // d-m-y format - 01-06-25, D-M-Y format - 01-Jun-2025, Y-m-d format - 2025-06-01
            'category'=> fake()->randomElement(['expense', 'salary', 'revenue', 'bank charges', 'maintenance']),
            'description' =>  fake()->paragraph(),
            'amount' => fake()->numberBetween(100, 9_999_999)
        ];
    }
}

```


### Generating Seedings

Laravel has a default `DatabaseSeeder.php` file in*database/seeders* directory. You can use that.
But you can also create brand new ones as needed.

```php title="DatabaseSeeder"
<?php

namespace Database\Seeders;

// use App\Models\User;
// use App\Models\Listing;
// use App\Models\Product;

use App\Models\Transaction;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    use WithoutModelEvents;

    /*** Seed the application's database.*/
    public function run(): void
    {
        // User::factory(10)->create();

        // User::factory()->create([
        //     'name' => 'Test User',
        //     'email' => 'test@example.com',
        // ]);

        // Listing::factory(20)->create();
        // Product::factory(20)->create();

        Trasaction::factory(10)->create();


    }

}

```
- It will not work right now goto your `App/Model/Transaction.php` add `HasFactory`

```php title="Transaction.php" hl_lines="4 8"
namespace App\Models;

use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Factories\HasFactory;

class Transaction extends Model
{
    use HasFactory;
}


``` 


```sh
php artisan db:seed
```

## Querying the Database

Use `php artisan tinker`

```sh
# Show all database records
Listing::all()
Product::all()
Transaction::all()
```

!!! note
    If your recent update is not working run `composer dumpautoload`, it should do the trick
    Then run your `php artisan tinker`

```sh
# How to complete the codeTo get all matching records:
$salaries = Transaction::where('category', 'salary')->get(); 
# OR
$salaries = Transaction::where('category','=', 'salary')->get(); # =, >, <, <=, >=

$trnx = Transaction::where('amount','<','500000')->get();    

# To get only the first matching record:
$firstSalary = Transaction::where('category', 'salary')->first();

#To count the matching records:
$count = Transaction::where('category', 'salary')->count();

# To check if any matching records exist:
$exists = Transaction::where('category', 'salary')->exists();

# SELECT * FROM transactions WHERE amount > 500000 AND category = 'bank charges'
Transaction::where('amount','>','500000')->where('category', 'bank charges')->count(); # 3

# SELECT * FROM transactions WHERE amount > 500000 OR category = 'bank charges'
Transaction::where('amount','>','500000')->orwhere('category', 'bank charges')->count(); # 9

# SELECT * FROM transactions WHERE amount > 500000 OR category = 'bank charges' ORDER BY date ASC
 Transaction::where('amount','>','500000')->orwhere('category', 'bank charges')
                                                ->orderby('date', 'asc')->get();

# SELECT * FROM transactions WHERE amount > 500000 OR category = 'bank charges' ORDER BY date ASC LIMIT 2
 Transaction::where('amount','>','500000')->orwhere('category', 'bank charges')
                                                ->orderby('date', 'asc')->limit(2)->get();
```

## Manual Update of DB Table

- Method #1
    ```sh
    $trn1 = new Transaction();
    $trn1->date = '24-09-26';
    $trn1->category = 'maintenance';
    $trn1->description = "lorem giggd desc.";
    $trn1->save();
    ```

- Method #2
    ```sh
    Transaction::create(['date'=>'24-09-26', 'category'=>'expense', 'description'=>'lorem summy via duo', 'amount'=>'345000']); 
    ```

    !!! note:
        Before the code below can work, make sure you add `protected fillable=...` fields you want fillable

        ```php hl_lines="6-11"
            ...
            class Transaction extends Model
            {
                use HasFactory;

                protected $fillable = [
                    'date',
                    'category',
                    'description',
                    'amount'
                ];
            }

        ```
