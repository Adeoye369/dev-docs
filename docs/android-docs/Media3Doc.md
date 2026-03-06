
# Media3, Exoplayer, Video Edit Doc

## Basic Exoplayer Setup

```kotlin title="MediaPickerScreen.kt"
package com.esenla.videoplayerv1

import ...

@Composable
fun MediaPickerScreen(
    modifier: Modifier = Modifier
){

    val context = LocalContext.current
    val player = retain{ 
        ExoPlayer.Builder(context.applicationContext).build() 
    }

    RetainedEffect(player) {
        onRetire {
            player.release()
        }
    }

    val videoPickerLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.PickVisualMedia()
    ) { uri ->
            uri?.let{
                player.setMediaItem(MediaItem.fromUri(uri))
                player.prepare()
                player.play()
            }
    }

    Column( modifier=modifier.fillMaxSize().padding(32.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.spacedBy(32.dp, Alignment.CenterVertically))
    {

        Button(
            onClick={
                videoPickerLauncher.launch(
                    PickVisualMediaRequest(
                        ActivityResultContracts.PickVisualMedia.VideoOnly
                    )
                )
        }){
            Text("Pick Video")
        }

        Box(modifier = modifier.fillMaxWidth().weight(1f)){
            ContentFrame(
                player = player,
                modifier = modifier.fillMaxSize()
            )
        }

    }
}
```

```kotlin title="MainActivity.kt"
package com.esenla.videoplayerv1

import ...

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            VideoPlayerV1Theme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    MediaPickerScreen(modifier= Modifier.fillMaxSize().padding(innerPadding))
                }
            }
        }
    }
}





```

