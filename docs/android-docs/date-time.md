# Working with Date and Time in Kotlin Android with JetPack Compose


## Getting the Days, Hours, Minutes and Secs Passed 

```kotlin
@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {


    var lastClickDate by remember { mutableStateOf<LocalDateTime?>(null) }
    var timeText by remember {mutableStateOf("X Days, X Hr, X min, X sec")}
    Column(...) {
        
        Text(text = "Hello $name!", modifier = modifier)
//        Text(text="Current date: ${now}")
        Text("Time Pass After Button Click:")
        Text(timeText)

        Button(
            onClick = {
                val now = LocalDateTime.now() // from java not kotlin
                        lastClickDate?.let { prev ->
                            val duration = Duration.between(prev, now)

                            // Duration times
                            val toDays = duration.toDays()
                            val toHours = duration.toHours() % 24
                            val toMin = duration.toMinutes() % 60
                            val toSec = duration.seconds % 60

                            // filter days
                                timeText += "\nClicked : " + when{
                                    toDays  > 0 ->    "$toDays Days, $toHours Hr, $toMin min, $toSec sec ago"
                                    toHours > 0 ->    "$toHours Hr, $toMin min, $toSec sec ago"
                                    toMin   > 0 ->    "$toMin min, $toSec sec ago"
                                    else  -> "$toSec sec ago"
                                }

                             }?: run{
                                 // first time click! click again to see the gap
                                 timeText = "Clicked : 0 sec ago"
                        }
                lastClickDate = now
                      },
            colors = ButtonDefaults.buttonColors()
        ) {
            Text(text = "CLICK TO UPDATE ")
        }
    }


}

```