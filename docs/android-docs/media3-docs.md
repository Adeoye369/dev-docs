
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

## Loading All video List from Device using MediaStore Api

```kotlin
fun isAndroid10andAbove() = Build.VERSION.SDK_INT >= Build.VERSION_CODES.R

fun createBitmapLocal(): ImageBitmap{
    // create mutable bitmap
    val bitmap = createBitmap(100, 100) // from `androidx.core` i.e. kotlins

    // set color with canvas
    val canvas = Canvas(bitmap) // Canvas/Color are from `android.gr` navtives 
    canvas.drawColor(Color.BLUE)

    return bitmap.asImageBitmap()
}

@Composable
fun ListVideoMediaStore(){
    val context = LocalContext.current
    val videoFiles = getVideo(context)
    LazyColumn {
        items(videoFiles) { video ->
            Card(modifier = Modifier.fillMaxWidth()) {
                Row(modifier = Modifier.padding(vertical = 5.dp)) {
                    val imageBitmap = getVideoThumbnail(video.uri, context)?.asImageBitmap()
                    Image(bitmap = imageBitmap as ImageBitmap, contentDescription = "",
                        contentScale = ContentScale.Crop,
                        modifier = Modifier.size(100.dp))

                    Column() {
                        Text(video.name, style = MaterialTheme.typography.bodyLarge,maxLines = 1, overflow = TextOverflow.Ellipsis)
                        Text("${ video.duration }")
                    }
                }
            }
        }
    }
}

data class Video(val uri: Uri, val name: String, val duration: Int)
fun getVideo(context: Context): List<Video>{
    // video list
    val videoList = mutableListOf<Video>()

    // Select collection based on android version {Basically Table}
    val collection =
        if (isAndroid10andAbove())
            MediaStore.Video.Media.getContentUri(MediaStore.VOLUME_EXTERNAL)
        else
            MediaStore.Video.Media.EXTERNAL_CONTENT_URI

    // Projection are basic, synonymous to fields column
    val projection = arrayOf(
        MediaStore.Video.Media._ID,
        MediaStore.Video.Media.DISPLAY_NAME,
        MediaStore.Video.Media.DURATION
    )


    // Query the context
    context.contentResolver.query(
        collection, projection,
        null, null,
        "${ MediaStore.Video.Media.DATE_ADDED } DESC"
    )?.use{cursor ->
        val idCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media._ID)
        val nameCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DISPLAY_NAME)
        val durationCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DURATION)

        while (cursor.moveToNext()){
            val id = cursor.getLong(idCol)
            val contentUri = ContentUris.withAppendedId(MediaStore.Video.Media.EXTERNAL_CONTENT_URI, id)
            videoList.add(Video(contentUri,  cursor.getString(nameCol), cursor.getInt(durationCol)) )
        }
    }

    return videoList
}

fun getVideoThumbnail(uri : Uri, context: Context): Bitmap? {

    val retriever = MediaMetadataRetriever()
    return try {
            retriever.setDataSource(context, uri)
            retriever.getFrameAtTime(2000000) // get frame at 2sec (in microseconds)

    }catch (e: Exception){
        null
    }finally {
        retriever.release()
    }
}
```

## Loading Select Video in a FilePath or Directory using MediaStore

### Get Video Via MediaStore

```kotlin
data class Video( val uri: Uri, val name: String, val duration: Int)
/**
 * @param {Context} context                  - Current App Context
 * @param {String?} selectedRelativePath     - Selected path by user
 * @return {List<Video>}                     - List of Video Data */
fun getVideo(context: Context, selectedRelativePath: String? = null): List<Video>{
    // video list
    val videoList = mutableListOf<Video>()


    // Select collection based on android version {Basically Table}

    val collection =  // search all External Volume directory {Database}
        if (isAndroid11andAbove()) MediaStore.Video.Media.getContentUri(MediaStore.VOLUME_EXTERNAL)
        else MediaStore.Video.Media.EXTERNAL_CONTENT_URI

    // Projection are basic, synonymous to {fields column}
    val projection = arrayOf(
        MediaStore.Video.Media._ID,
        MediaStore.Video.Media.DISPLAY_NAME,
        MediaStore.Video.Media.DURATION
    )



    // Filter for files located specifically in the Selected directory
    val selection = if(selectedRelativePath?.isNotEmpty() == true) "${MediaStore.Video.Media.RELATIVE_PATH} LIKE ?" else null
    val selectionArgs = if(selectedRelativePath?.isNotEmpty() == true ) arrayOf("${selectedRelativePath}/%") else null

    // Query the context
    context.contentResolver.query(
        collection,
        projection,
        selection,
        selectionArgs,
        "${ MediaStore.Video.Media.DATE_ADDED } DESC"
    )?.use{cursor ->
        val idCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media._ID)
        val nameCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DISPLAY_NAME)
        val durationCol = cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DURATION)

        while (cursor.moveToNext()){

            val contentUri = ContentUris.withAppendedId(
                MediaStore.Video.Media.EXTERNAL_CONTENT_URI,
                cursor.getLong(idCol)
            )

            videoList.add(
                Video(
                    uri = contentUri,
                    name = cursor.getString(nameCol),
                    duration = cursor.getInt(durationCol)
                )
            )
        }
    }

    return videoList
}
```

### Helper functions for UI to loadThumbnail and getPath from URI

```kotlin
fun getVideoThumbnail(uri : Uri, context: Context): Bitmap? {

   return if(isAndroid10andAbove()){
        try {
            context.contentResolver.loadThumbnail(uri, Size(320, 240), null)
        }catch (e: Exception){
            null
        }
    } else{
        val retriever = MediaMetadataRetriever()
        try {
            retriever.setDataSource(context, uri)
            retriever.getFrameAtTime(2000000) // get frame at 2sec (in microseconds)

        }catch (e: Exception){
            null
        }finally {
            retriever.release()
        }
    }


}


fun getRelativePathFromDocumentTreeUri(treeUri: Uri): String? {
    val path = treeUri.path ?: return null

    // SAF URIs often look like /tree/primary:Folder01/subFolder01/MyFolder
    // We need only the "Folder01/subFolder01/MyFolder" path
    return if(path.contains(":")){
       val split =  path.split(":")
        if(split.size > 1) return split[1] else null
    } else null

}
```

### UI to Selected files and load it 

```kotlin
@Composable
fun ListVideoMediaStoreScreen(){
    val context = LocalContext.current
    var videoFiles : List<Video> by remember { mutableStateOf(emptyList()) }
    var isLoading by remember { mutableStateOf(true) }
    var selectedRelativePath: String? by remember { mutableStateOf("") }

    var fileLaucher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.OpenDocumentTree()
    ) {
        uri ->
        uri?.let {
            context.contentResolver.takePersistableUriPermission(it, Intent.FLAG_GRANT_READ_URI_PERMISSION)
            selectedRelativePath = getRelativePathFromDocumentTreeUri(it)
            Log.d("MVM", "Selected Uri: ${it.path}")
        }

    }


//    val videoFiles = getVideo(context)
    LaunchedEffect(videoFiles, selectedRelativePath) {
            isLoading = true
            videoFiles = withContext(Dispatchers.IO) {
                getVideo(context, selectedRelativePath)
            }

            isLoading = false
    }

    if(isLoading) {
        Box(contentAlignment = Alignment.Center, modifier = Modifier.fillMaxSize()) {
        CircularProgressIndicator(strokeWidth = 10.dp, modifier = Modifier.size(200.dp))
        }
    }
    else
        LazyColumn {

            items(videoFiles) { video ->
                Card(modifier = Modifier.fillMaxWidth()) {
                    Row(modifier = Modifier.padding(vertical = 5.dp)) {

                        val imageBitmap = getVideoThumbnail(video.uri, context)?.asImageBitmap()

                        Image(bitmap = imageBitmap as ImageBitmap, contentDescription = "",
                            contentScale = ContentScale.Crop,
                             modifier = Modifier.size(100.dp)
                                    )
                        Column{
                            Text(video.name, style = MaterialTheme.typography.bodyLarge,maxLines = 1, overflow = TextOverflow.Ellipsis)
                            Text("${ video.duration }")
                        }
                    }
                }
            }

    }

    Box(contentAlignment = Alignment.Center, modifier = Modifier.fillMaxSize()){
        IconButton(onClick = {
            fileLaucher.launch(null)
        }) {
            Icon(Icons.Default.AddCircle, "",
                modifier = Modifier.size(200.dp))
        }
    }
}


```
