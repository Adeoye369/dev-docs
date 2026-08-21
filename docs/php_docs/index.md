# intro to Php

1. Using only VSCode
   - download lastest stable version of php 
   - Install it an add it to environment path
   - in vscode, download **PHP Intelephense** extension and disable @builtin **PHP Features** extension.
   - Then download **PHP Server** extension. You should be good to go
  
2. using XAMPP
   - Download xampp and install it
   - Launch the Xampp control and start *Apache* and *Mysql*
   - go to `C/xampp/htdocs` and input your website to work on 


## Basic example 

```php title="index.php"
<!DOCTYPE html>
<html lang="en">
<head>
    <?php include('pure_code.php') ?>
</head>
<body>
    <!-- TODO   finish the current trial -->
    <h1><?php echo "Hello from Htdocs"; ?></h1>
    <h2><?php echo "Some more php"; ?></h2>
    <h3><?php echo "Yet Another basic php"; ?></h3>

    <?php if(false){?>
        <p>Some new text goes here</p>
    <?php } else { ?>
        <p>Some OLDER text goes</p>
        <?php } ?>
</body>
</html>
```

```php title="pure.php"
<?php 

echo '
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>⭐ From Pure PHP ⭐</title>
';

```

## Working With Variable and Data type

```php
   <?php $username = "Ade" ?>

    <?php if($username) {?>
        <h1>Hello, <?php echo $username ?></h1>
    <?php }else{?>
        <h1>Hello, User</h1>
    <?php } ?>

<?php 
    // scalar types
    $username = "Ade";
    $daysLeft = 45;
    $score = 167.5;
    $isFinished = false;
    
    // Array types
    $users = ["Tolu", 53, "Buki", "tomi"];
    
    ?>

```

## Working with Array in PHP

```php
<?php 
        $var1 = "say Hello GLOBAL";

         function addProduct(){
            $var1 = "Say hello";
            global $var1; // using the global $var1 instead 

            return $var1;
        }
        
        echo "<p>".addProduct()."</p>";
        echo "<p>".$var1."</p>";

        
        // Associative array in php
        $students = ["segun"=> 34, "Taiwo"=>56, "Bukky"=>34, "Funmi"=> 100];

        foreach($students as $student => $score ){
            echo "<p>". $student ." score is = ". $score. "</p>";
        }
   ?>
```
