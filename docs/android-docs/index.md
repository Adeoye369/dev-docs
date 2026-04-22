
# Android Dev Note

## Basic Image Handling

```kotlin
    Image(painter = painterResource(R.drawable.pose_pic),
            contentDescription = "Pose Pic",

            // Basic Tint
//            colorFilter = ColorFilter.tint(color=Color.Blue.copy(alpha=0.5f), blendMode = BlendMode.Lighten)

            // Using Complex Matrix
//            colorFilter = ColorFilter.colorMatrix(ColorMatrix().apply{setToSaturation(0f)})

            // multiplying image
//            colorFilter = ColorFilter.lighting(multiply = Color.Green, add = Color.Black)
        )
```

## Importing Image Resources

```kotlin

@Composable
fun ImageCard( painter: Painter, contentDesc: String, title:String,  modifier: Modifier = Modifier){
    Box(modifier = Modifier.fillMaxWidth(.5f).padding(16.dp)) {
        Card(modifier = modifier.fillMaxWidth(), shape = RoundedCornerShape(15.dp)) 
        {
            Box(modifier = Modifier.height(200.dp).fillMaxWidth()) {

                // Image Displayed
                Image( painter = painter, contentDescription = contentDesc, contentScale = ContentScale.Crop)

                // Gradient Background
                Box(
                    modifier = modifier.fillMaxSize().background(
                        Brush.verticalGradient(colors = listOf(Color.Transparent, Color.Black),startY = 400f)
                        )
                )

                // Image Title
                Box(
                    modifier = modifier.fillMaxSize().padding(12.dp),
                    contentAlignment = Alignment.BottomStart
                ) {
                    Text(title, style = TextStyle(Color.White), fontSize = 16.sp)
                }
            } // Box

        } // Card
    }// end Box
}

// Usage of function
    @Composable
    fun SomeDisplay(){

        val desc = "This is the face of victory"
        val title = "Face Off, Victory time"
        val face1 = painterResource(id = R.drawable.face_a)
        val car1 = painterResource(id = R.drawable.car_a)
        val face2 = painterResource(id = R.drawable.face_b)

        Column(modifier = Modifier.fillMaxSize(), verticalArrangement = Arrangement.SpaceAround, horizontalAlignment = Alignment.CenterHorizontally) {

                ImageCard(painter =face1, contentDesc = desc, title = title)
                ImageCard(painter =car1, contentDesc = desc, title = title)
                ImageCard(painter =face2, contentDesc = desc, title = title)
        }
    }


```

![alt text](img/image-3.png)

## Basic Scaffolding w/ Topbar

### Basic 1

```js
 Scaffold(
        modifier = Modifier.fillMaxSize(),

        topBar = { TopAppBar(
            title = { Text("TextQ") } ,
            navigationIcon = {Icon(imageVector = Icons.Default.Home, contentDescription = null)  },
            actions ={
                IconButton(onClick = {}) {Icon(imageVector = Icons.Default.Search, contentDescription = null)}
                IconButton(onClick = {}) {Icon(imageVector = Icons.Default.AddCircle, contentDescription = null)}
            }
            ) },

           bottomBar = {
            NavigationBar() {
                NavigationBarItem(
                    selected = false, onClick = {},
                    icon = { Icon(imageVector = Icons.Filled.Create, contentDescription = null) }
                )
                NavigationBarItem(
                    selected = false, onClick = {},
                    icon = { Icon(imageVector = Icons.Filled.Build, contentDescription = null) }
                )
            }
        },
                    },
        snackbarHost = {SnackbarHost(hostState = snackBar, modifier = Modifier.imePadding())}

    ){ /* paddingValues -> */
        Column(
            modifier = Modifier
                .padding(top = it.calculateTopPadding()).fillMaxHeight(.2f),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = AbsoluteAlignment.Right
        ) {
            ...
        }
    }
```

![screen shot of app activity](<img/Screenshot 2025-12-01 043315.png>)

## Fields

### TextFields and Button

```js

    val snackbar = remember{ SnackbarHostState() }
    var textField by remember{ mutableStateOf("")}
    val scope = rememberCoroutineScope()
...

    TextField(
        modifier = Modifier.fillMaxWidth().height(50.dp),
        value = textField,
        onValueChange = {textField = it},
        label = {Text("Input your name")},
        singleLine = true
    )

    Spacer(modifier = Modifier.height(20.dp).fillMaxWidth())
    Button(
        onClick = {
            scope.launch {
                snackbar.showSnackbar("Hello $textField")
            }
        }){ Text("Click Me!") }
```
![alt text](img/image-1.png)


## LazyColumn List Loading

```js
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
//        enableEdgeToEdge()
        setContent {
            ListFoodItems()
        }
    }
}


@Composable
fun ListTask(){
    Column(modifier = Modifier.fillMaxSize(), 
    verticalArrangement = Arrangement.Center,
     horizontalAlignment = Alignment.CenterHorizontally){
        for (i in 1 ..50)
        {
            Text("Item $i",
                fontWeight = FontWeight.ExtraBold,
                fontSize = 50.sp)
        }
    }
}

@Preview(showBackground = true)
@Composable
fun ListFoodItems(){
    val itemsIndxList = listOf("food1", "bread", "fufu","food2", "Rice", "Bread", "Egusi", "Ogbono", "Ewedu", "Ajekuke")
    LazyColumn(modifier = Modifier.fillMaxWidth())
    {
        items(50){
            val i1 = it + 1
            Text("Item $i1", fontSize = 25.sp)
            
        }
       itemsIndexed(itemsIndxList) {ind, str ->
           Row() {
               Text(" $ind ", fontSize = 12.sp)
               Spacer(Modifier.width(5.dp))
               Text( str, fontSize = 25.sp, fontStyle = FontStyle.Italic)

           }
       }
    }
}
```
![alt text](img/image-2.png)


## New Library catalogue declaration

implementation("androidx.constraintlayout:constraintlayout-compose:1.1.1") in the new library catalog declaration


## Navigation Menu Code

```js

enum class AppDestinations(val label: String, val icon: ImageVector) {
    HOME("Home", Icons.Default.Home),
    FAVORITES("Favorites", Icons.Default.Favorite),
    PROFILE("Profile", Icons.Default.AccountBox),
    ADD("Add Note", Icons.Default.AddCircle )
}

fun MyApplication001App() {
    var currentDestination by rememberSaveable { mutableStateOf(AppDestinations.HOME) }

    NavigationSuiteScaffold(
        navigationSuiteItems = {
            AppDestinations.entries.forEach {
                item(
                    icon = { Icon(imageVector = it.icon, contentDescription = it.label)
                    },
                    label = { Text(it.label) },
                    selected = it == currentDestination,
                    onClick = { currentDestination = it }
                )
            }
        }
    ) {
        Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
            Greeting(
                name = "Android",
                modifier = Modifier.padding(innerPadding)
            )
        }
    }
}

```
<figure markdown='span'>
    ![alt text](img/image-4.png)
</figure>


## ExposedDropdownMenu - (Spinner)

```js
Column(modifier = modifier.padding(16.dp),
            horizontalAlignment = Alignment.Start, verticalArrangement = Arrangement.SpaceEvenly) {

            var isExpanded by remember { mutableStateOf(false) }
            val priorityList = listOf( "Low", "Medium", "High")
            var priorityText by remember { mutableStateOf(priorityList[0]) }

            var task by remember{mutableStateOf("")}
            // For the input side

                ExposedDropdownMenuBox(
                    modifier = Modifier.height(50.dp),
                    expanded = isExpanded,
                    onExpandedChange = {isExpanded = !isExpanded}
                ) {
                    TextField(
                        value = priorityText,
                        onValueChange = {  },
                        readOnly = true,
                        trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded=isExpanded)},
                        colors = ExposedDropdownMenuDefaults.textFieldColors(),
                        modifier = Modifier.menuAnchor(type = ExposedDropdownMenuAnchorType.PrimaryNotEditable, enabled = !isExpanded)
                    )

                    ExposedDropdownMenu(
                        expanded = isExpanded,
                        onDismissRequest = { isExpanded = false}
                    ) {
                        priorityList.forEach { item ->
                            DropdownMenuItem(
                                text = { Text( item, color = MaterialTheme.colorScheme.onSurface) },
                                onClick = {
                                        priorityText = value
                                        isExpanded=false
                                },
                                contentPadding = ExposedDropdownMenuDefaults.ItemContentPadding
                            )
                        }

                    }
                }
            

            Spacer(Modifier.height(10.dp))

            Text("Currently Selected Priority = $priorityText" )


```

## .let{...} usage

1. What does it do?
   - **uri? (Safe Call):** The question mark checks if uri is null. If uri is null, the entire expression returns null and skips the block entirely, preventing a NullPointerException.

    -**.let (Scope Function):** If uri is not null, let executes the block of code inside {}.

   - **it (Context Object):** Inside the {} block, the non-null uri
  object is referenced by the keyword `it`.

```kotlin
// Example: Selecting an image
val getResult = rememberLauncherForActivityResult(ActivityResultContracts.GetContent()) { uri: Uri? ->
    // 'uri' can be null if the user cancelled
    uri?.let {
        // This code only runs if 'uri' is NOT null.
        // 'it' refers to the non-null Uri object.
        imageView.setImageURI(it) 
    }
}
```

## .apply{...} usage

1. Initializing Views or Objects (Replacing Builder Pattern)

    Instead of repeating the variable name multiple times,
    apply makes initialization cleaner.

    ```kotlin
    // Without apply
    val textView = TextView(context)
    textView.text = "Hello"
    textView.textSize = 20f
    textView.setTextColor(Color.BLACK)

    // With apply
    val textView = TextView(context).apply {
        text = "Hello"
        textSize = 20f
        setTextColor(Color.BLACK)
    }
    ```

2. Configuring Intent Extras or Bundles

    ```kotlin
    val intent = Intent(this, SecondActivity::class.java).apply {
        putExtra("KEY_ID", 101)
        putExtra("KEY_NAME", "Kotlin")
    }
    launcher.launch(intent)

    ```

3. Modifying Properties of a Recently Created Object

```kotlin

```

## .also{...} usage

### Key Characteristics

**Context Object:** Inside the curly braces, the object is referred to as it by default (or you can give it a custom name).

**Return Value:** It always returns the object it was called on, regardless of what the code inside the block does.

**Mnemonic:** Read it as "do this to the object, and also do the following...".

### Common Use Cases in Android

**Logging and Debugging:** You can peek at a variable's value in a chain of calls without breaking the chain.

```kotlin
val result = getAppData()
    .also { println("Data received: $it") } // Logs the data
    .map { it.toUiModel() }               // Continues with original data
```

**Side Effects during Initialization:** Performing additional tasks, like adding an object to a list or starting a background process, immediately after creating it.
```kotlin
data class User(val name: String, var email: String = "")

fun main() {
    // Using .also to log an object after initialization
    val user = User("Alice").also {
        // SIDE EFFECT: Logging/Validation happens here
        println("Initializing user: $it")
        
        // Setting a default value
        it.email = "alice@example.com"
    }
    
    println("Final User: $user")
}
```

**Validation:** Checking an object's state before it is returned or used further in the code.

```kotlin
data class User(val name: String, val age: Int)

fun createUser(name: String, age: Int): User {
    return User(name, age).also { user -> // or _ and just use `it`
        // Validation logic
        require(user.name.isNotBlank()) { "Name cannot be blank" }
        require(user.age >= 18) { "User must be an adult" }
        
        // Logging as a secondary side effect
        println("Validated user: ${user.name}")
    }
}
```

### .also vs. .apply

While both return the original object, they differ in how you access that object:
`.also` uses `it`: **Best for actions that refer to the object as a whole** (like logging).
`.apply` uses `this`: **Best for object configuration where you want to call the object's methods or set properties directly** (like `this.color = "Red"`).

### Comparison with Java

```java
List<String> names = getNames();
System.out.println("Processing: " + names); // Extra lines of code
save(names); 
```

```kotlin
val names = getNames()
    .also { println("Processing: $it") } // Peeks at the data "on the side"
    .also { save(it) } // Can even chain multiple side effects
```

## let{it ...}, apply{this ...}, also{it ...} more examples

```kotlin
kotlin
// 1. apply: Great for setting up the View's properties directly
val myTextView = TextView(context).apply {
    text = "Hello World"
    setTextColor(Color.RED)
    setOnClickListener { /* click logic */ }
}

// 2. also: Perfect for logging the View after it's initialized
myTextView.also {
    Log.d("UI_DEBUG", "TextView created with text: ${it.text}")
}

// 3. let: Excellent for safely handling nullable data for the UI
val username: String? = fetchUser()
username?.let {
    myTextView.text = "Welcome, $it!" // Only sets text if username is not null
}
```

## Nullability in Kotlin

In Kotlin, (selectedRelativePath!!.isNotEmpty()) is a conditional check used to ensure a nullable variable is **not null AND not an empty string ("")**, asserting that it will not be null at that moment.

- **`selectedRelativePath`**: A variable of type String? (nullable string), meaning it can hold a string or null.
  
- **!! (Not-null assertion operator)**: This forces the compiler to treat the variable as non-null. If selectedRelativePath is null, this will throw a NullPointerException.

**`.isNotEmpty()`**: A standard function that returns true if the string length is greater than 0

```kotlin
fun main() {
    var selectedRelativePath: String? = "/home/user/file.txt"

    // Example 1: Non-null and non-empty (Passes)
    if (selectedRelativePath!!.isNotEmpty()) {
        println("Path is: $selectedRelativePath") // Output: Path is: /home/user/file.txt
    }

    // Example 2: Empty string (Fails isNotEmpty, returns false)
    selectedRelativePath = ""
    if (selectedRelativePath!!.isNotEmpty()) {
        println("This will not print")
    } else {
        println("Path is empty") // Output: Path is empty
    }

    // Example 3: Null (Throws NullPointerException)
    selectedRelativePath = null
    try {
        if (selectedRelativePath!!.isNotEmpty()) {
            println("This will not print")
        }
    } catch (e: NullPointerException) {
        println("Caught error: $e") // Output: Caught error: java.lang.NullPointerException
    }
}
```

### Safer, Idiomatic Alternatives

Using !! is risky. Kotlin developers prefer these safer alternatives:

1. `!selectedRelativePath.isNullOrEmpty()`(Recommended): Returns true if not null AND not empty.

    ```kotlin
    if (!selectedRelativePath.isNullOrEmpty()) { ... }
    ```

2. `selectedRelativePath?.isNotEmpty() == true:` Safe call. Returns false if the variable is null.

    ```kotlin
    if (selectedRelativePath?.isNotEmpty() == true) { ... }
    ```
