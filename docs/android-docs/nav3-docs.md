# Navigation 3 - Documentation

## Dependencies

Here are the minimum dependencies required for Nav3

```gradle
    implementation("androidx.navigation3:navigation3-ui:1.0.1")
    implementation("androidx.navigation3:navigation3-runtime-android:1.0.1")
    implementation("org.jetbrains.kotlinx:kotlinx-serialization-core:1.9.0")
    implementation("androidx.lifecycle:lifecycle-viewmodel-navigation3:2.11.0-alpha02")
    implementation("androidx.compose.material3.adaptive:adaptive-navigation3:1.3.0-alpha09")
```

To Navigtion Navigation 3, add the following to your `libs.versions.toml` file

```toml title="libs.versions.toml"
    [versions]
    nav3Core = "1.1.2"
    lifecycleViewmodelNav3 = "2.11.0-beta02"
    kotlinSerialization = "2.2.21"
    kotlinxSerializationCore = "1.9.0"
    material3AdaptiveNav3 = "1.3.0-beta02"

    [libraries]
    # Core Navigation 3 libraries
    androidx-navigation3-runtime = { module = "androidx.navigation3:navigation3-runtime", version.ref = "nav3Core" }
    androidx-navigation3-ui = { module = "androidx.navigation3:navigation3-ui", version.ref = "nav3Core" }

    # Optional add-on libraries
    androidx-lifecycle-viewmodel-navigation3 = { module = "androidx.lifecycle:lifecycle-viewmodel-navigation3", version.ref = "lifecycleViewmodelNav3" }
    kotlinx-serialization-core = { module = "org.jetbrains.kotlinx:kotlinx-serialization-core", version.ref = "kotlinxSerializationCore" }
    androidx-material3-adaptive-navigation3 = { group = "androidx.compose.material3.adaptive", name = "adaptive-navigation3", version.ref = "material3AdaptiveNav3" }

    [plugins]
    # Optional plugins
    jetbrains-kotlin-serialization = { id = "org.jetbrains.kotlin.plugin.serialization", version.ref = "kotlinSerialization"}

```

Also, update your compile SDK to 36 or later:

````gradle
[versions]
compileSdk = "36"
````

Add the following to your app build file `app/build.gradle.kts`:

```gradle
 plugins {
    ...
    // Optional, provides the @Serialize annotation for autogeneration of Serializers.
    alias(libs.plugins.jetbrains.kotlin.serialization)
}

dependencies {
    ...
    implementation(libs.androidx.navigation3.ui)
    implementation(libs.androidx.navigation3.runtime)
    implementation(libs.androidx.lifecycle.viewmodel.navigation3)
    implementation(libs.androidx.material3.adaptive.navigation3)
    implementation(libs.kotlinx.serialization.core)
}
```

## Basic Example with Home

```kotlin title="MainActivity.kt"

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Nav3UIDisplay001Theme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    AppRoot(Modifier.padding(innerPadding))
                }
            }
        }
    }
}


@Serializable
sealed interface Route : NavKey {

    @Serializable
    data object Home : Route
    @Serializable
    data class Profile(val id: String) : Route
}

@Composable
fun AppRoot(modifier: Modifier = Modifier){

    val backStack = remember{mutableStateListOf<Any>(Route.Home)}

    NavDisplay(
        backStack = backStack,
        onBack = { backStack.removeLastOrNull() },
        entryProvider = entryProvider {
            entry<Route.Home>{
                HomeScreen(
                    mod=modifier,
                    onProfileClick = { userid ->
                    backStack.add(Route.Profile(userid))
                })
            }
            entry<Route.Profile> {
                ProfileScreen {
                    backStack.removeLastOrNull()
                }
            }
        }
    )

}

@Composable
fun HomeScreen(mod:Modifier, onProfileClick:(userid:String)->Unit){
    Column(
        modifier = mod.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally

    ) {
        Text("Hello Home")
        Button(
            onClick = { onProfileClick("uid001") }
        ){
            Text("To Profile")
        }
    }

}

@Composable
fun ProfileScreen(onBackClick: ()->Unit){

    Box(
        contentAlignment = Alignment.Center,
        modifier = Modifier.fillMaxSize()
    ){
        Row(
            horizontalArrangement = Arrangement.Center,
            verticalAlignment = Alignment.CenterVertically,
            modifier = Modifier.padding(12.dp)

        ){

            IconButton(
                onClick = onBackClick
            ) {
                Icon(Icons.Default.ArrowBackIosNew, "Back")

            }
            Spacer(modifier = Modifier.width(20.dp))
            Text("Back to Home")
        }
    }

}


```
