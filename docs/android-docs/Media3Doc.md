
# Media3, Exoplayer, Video Edit Doc

Here are the basic dependencies that are needed

```kts
    implementation("androidx.media3:media3-common-ktx:1.9.2")
    implementation("androidx.media3:media3-ui-compose:1.9.2")
    implementation("androidx.media3:media3-ui-compose-material3:1.9.2")
    implementation("androidx.media3:media3-exoplayer:1.9.2")
    implementation("androidx.compose.runtime:runtime:1.8.0-alpha01") // Or newer
```

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

## Media3, Exoplayer FINISHED BASIC DOC

### MediaPickerScreen.kt

```kotlin title="MediaPickerScreen.kt"
package com.esenla.videoplayerv2

import ...


@Composable
fun MediaPickerScreen( modifier: Modifier){

    val context = LocalContext.current
    val player = retain{ExoPlayer.Builder(context.applicationContext).build()}

    var isPlaying by retain { mutableStateOf(false) }
    var currentPosition by retain { mutableLongStateOf(0L) }
    var duration by retain { mutableLongStateOf(0L) }
    var isSeeking by retain { mutableStateOf(false) }
    var isBuffering by retain { mutableStateOf(false) }
    var isPlayerUiVisible by retain { mutableStateOf(false) }

    val videoLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.PickVisualMedia()
    ) {
        uri -> uri?.let {
            player.setMediaItem(MediaItem.fromUri(uri))
            player.prepare()
            player.play()
    }

    }


    RetainedEffect(key1=player){
        val listener = object : Player.Listener{
            override fun onIsPlayingChanged(playing: Boolean) {
                super.onIsPlayingChanged(playing)
                isPlaying = playing
            }

            override fun onPlaybackStateChanged(playbackState: Int) {
                super.onPlaybackStateChanged(playbackState)
                isBuffering = playbackState == Player.STATE_BUFFERING
                if(playbackState == Player.STATE_READY ){
                    duration = player.duration.coerceAtLeast(0)
                }
            }

        }
        player.addListener(listener)

        onRetire(){
            player.removeListener(listener)
            player.release()
        }
    }

    LaunchedEffect( isPlayerUiVisible, isSeeking, isPlaying) {
        delay(5000L) // if after 5secs we are not seeking hide
        if(!isSeeking) isPlayerUiVisible = false
        
    }

    LaunchedEffect(player, isPlaying, isSeeking) {
        // update seeking track, at 60fps?
        while (isPlaying){
            if(!isSeeking) currentPosition = player.currentPosition.coerceAtLeast(0)
            delay(16L) // 1000ms/60frame = 16 frames
        }
    }

    // Column to hold video
    Column(
        modifier = modifier.fillMaxSize(),
        verticalArrangement = Arrangement.spacedBy(10.dp, Alignment.CenterVertically),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {

        // Picker Button
        Button(
            onClick = {
                videoLauncher.launch(
                    input = PickVisualMediaRequest(
                        mediaType = ActivityResultContracts.PickVisualMedia.VideoOnly)
                )
            }
        ) {
            Text("PickVideo")
        }

        // Content Frame container
        Box(
            modifier= Modifier.weight(1f)

        ){
            ContentFrame(
                player=player,
                modifier= Modifier.fillMaxWidth()
                    .clickable( 
                        interactionSource = null, 
                        indication = null,
                ){
                    isPlayerUiVisible = !isPlayerUiVisible
                }
            )

            Column(
                modifier= Modifier.fillMaxSize()
            ) {
                AnimatedVisibility(
                    visible = isPlayerUiVisible,
                    enter = fadeIn(),
                    exit = fadeOut()
                ) {
                    PlayerUi(
                        isPlaying = isPlaying,
                        duration = duration,
                        currentPosition = currentPosition,
                        isBuffering = isBuffering,
                        onSeekBarPositionChange = { pos->
                            isSeeking = true
                            currentPosition=pos
                        },
                        onSeekBarPositionChangeFinished = { newPos ->
                            player.seekTo(newPos)
                            isSeeking=false
                        },
                        onPlayPauseClick = {
                            when{
                                !isPlaying && player.playbackState == Player.STATE_ENDED->{
                                    player.seekTo(0)
                                    player.play()
                                }
                                !isPlaying -> player.play()
                                isPlaying -> player.pause()
                            }
                        }
                    )
                }
            }

        }// end Box


    }

}
```

### PlayerUi.kt

```kotlin
package com.esenla.videoplayerv2

import . . . .

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun PlayerUi(
    isPlaying : Boolean,
    currentPosition: Long,
    duration: Long,
    isBuffering: Boolean,
    onSeekBarPositionChange: (Long)-> Unit,
    onSeekBarPositionChangeFinished: (Long) -> Unit,
    onPlayPauseClick: () -> Unit

){
    // Overall Box - Apply Gradient Overlay drawing
    Box(
        modifier = Modifier
            .fillMaxSize()
            .background( 
                brush = Brush.verticalGradient(listOf(Color.Transparent, Color.Black))
            ),
        contentAlignment = Alignment.Center
    ){
        // Display Circular Progress indicator
        if(isBuffering){
            CircularProgressIndicator(strokeWidth = 5.dp, 
            trackColor = ProgressIndicatorDefaults.circularColor,
                modifier = Modifier.size(20.dp))
        }

        // Display play and pause
        IconButton(
            onClick = onPlayPauseClick,
            modifier = Modifier.size(100.dp)
        ) {
            Icon(
                imageVector = if (isPlaying) ImageVector.vectorResource(R.drawable.pause_24)
                                else ImageVector.vectorResource(R.drawable.play_24),
                contentDescription = if(isPlaying) "Pause" else "Play",
                modifier = Modifier.size(50.dp),
                tint = Color(0.5f, 0.5f, 0.5f, 1.0f)
            )

        } // end IconButton

        //Player Slide
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .align(alignment = Alignment.BottomCenter).padding(10.dp),
            horizontalArrangement = Arrangement.spacedBy(10.dp),
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(formatDuration(currentPosition), color= Color.White)
            Slider(
                value=currentPosition.toFloat(),
                valueRange = 0f .. duration.toFloat(),
                onValueChange = {newPos-> onSeekBarPositionChange(newPos.toLong())},
                onValueChangeFinished = {onSeekBarPositionChangeFinished(currentPosition)},

                thumb = {
                    Box(modifier = Modifier.size(15.dp)
                        .shadow(elevation = 4.dp, CircleShape).background(Color.White))
                },
                track = { sliderState ->
                    Box(modifier = Modifier.fillMaxWidth().height(4.dp)
                        .clip(RoundedCornerShape(2.dp))
                        .background(color= MaterialTheme.colorScheme.surfaceVariant)){
                        Box(
                            modifier = Modifier
                                .fillMaxWidth(sliderState.value / duration)
                                .fillMaxHeight()
                                .background(MaterialTheme.colorScheme.primary)
                        )
                    }
                },
                
                 modifier = Modifier.weight(1f)
            )
            Text(formatDuration(duration), color= Color.White)
        }// end Row - Slider


    }// end Box

} // end PlayerUi

// format playtime duration
fun formatDuration(millis: Long): String{
    val totalSecs = millis / 1000
    val hours = totalSecs / 3600
    val minutes = (totalSecs % 3600) / 60
    val secs = totalSecs % 60



    return if(hours > 0) String.format(Locale.US, "%d:%02d:%02d", hours, minutes, secs)
            else String.format(Locale.US, "%02d:%02d", minutes, secs)

}
```
