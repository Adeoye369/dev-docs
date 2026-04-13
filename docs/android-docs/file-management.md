# Documentation for File Handling

Here demonstract how to get directory from App specific Directory

## Accessing Files and Directory in App-Specific Directory

```kotlin
@Composable
fun internalFoldersAndFilesList(): List<File>{
    val context = LocalContext.current

    // Access App specific external directory
    val folder = context.getExternalFilesDir(null)
    val files = folder?.listFiles()?.toList() ?: emptyList()

    return files
}
```

Saving File to App Specific Directory

```kotlin
fun SaveFileToInternalDir() {

    val context = LocalContext.current
    Button(
        onClick = {

            //  create folder and file name
            val picFolderName = "Fold/2026/April"
            val filename = "Pic001.txt"

            // Get App specific Directory
            val appBaseDir = context.getExternalFilesDir(null) // com.esenla.vidframe/files
            val picFolder = File(appBaseDir, picFolderName)

            // Create directory if not exist
            if (!picFolder.exists()) picFolder.mkdirs()

            // Create and write to file Directory
            val picFile = File(picFolder, filename)

            try {
                picFile.writeText("This is file For Pic001")
            } catch (e: IOException) {
                e.printStackTrace()
            }

        }
    ) {
        Text("Create Files")
    }
}
```

## Accessing System Root Files and Directory

1. Set Permission in Android Manifest

    ```xml
    <?xml version="1.0" encoding="utf-8"?>
    <manifest xmlns:android="http://schemas.android.com/... >
        <!-- Android 11+ -->
        <uses-permission android:name="android.permission.MANAGE_EXTERNAL_STORAGE" />

        <!-- Android 10 and Below -->
        <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE"/>
        <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>

        <application
            android:allowBackup="true"
            <!--  -->
        </application>

    </manifest>

    ```

2. Use LauncherActivityResult.. to request permission

    ```kotlin
    package com.esenla.vidframe


    @Composable
    fun ListRootFoldersAndFiles (){
        val context = LocalContext.current

        val fileAccessLauncher = rememberLauncherForActivityResult(
            contract = ActivityResultContracts.StartActivityForResult()
        ) {_->
            if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.R){

                // If User Grants Permission Access
                if(Environment.isExternalStorageManager()){
                    Toast.makeText(context, " ✅ Root Access Granted", Toast.LENGTH_SHORT).show()

                    // List Files and Directories
                    val root = Environment.getExternalStorageDirectory()
                    val files = root.listFiles()
                    files?.forEach { f ->
                        if(f.isDirectory)   Log.d("TAG","Directory:  ${f.name}")
                        else                Log.d("TAG", "    File:  ${f.name}")

                    }
                }
                else{
                    Toast.makeText(context, "❌ Permission Denied", Toast.LENGTH_SHORT).show()
                }
            }
        }

        Button(onClick = {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                if (!Environment.isExternalStorageManager()) {
                    val intent = Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION)
                        .apply {
                            // Go to this App Permission ONLY
                            data = "package:${context.packageName}".toUri()
                    }

                    fileAccessLauncher.launch(intent)


                }
            }
        }) {
            Text("Grant Root Access")
        }
    }
    ```

## Reading User-Selected Directories using the Storage Access Framework (SAF)

```kotlin

/**
 * Read User-Selected Directories (SAF)
 * ===================================
 * To access public folders like "Downloads" or custom directories, use "ActivityResultContracts.OpenDocumentTree".
 * This returns a Uri that you can use to list files via "DocumentFile" */

@Composable
fun ListSelectedDir(){

    val context = LocalContext.current
    var directoryUri by remember{ mutableStateOf<Uri?>(null) }

    val fileLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.OpenDocumentTree()
    ) { uri ->
        directoryUri = uri
    }

    Box(modifier=Modifier.fillMaxSize().background(Color(0.251f, 0.384f, 0.298f, 1.0f)), contentAlignment = Alignment.Center) {
        Column() {
            Button(onClick = { fileLauncher.launch(null) }) { Text("Select Folder")}
            SelectedFolderContent(context, directoryUri)
        }
    }


}

/**
 * List Files from the Selected URI* */
@Composable
fun SelectedFolderContent(context: Context, uri: Uri?,){
    val documentFile = uri?.let { DocumentFile.fromTreeUri(context, it) }

    val files = documentFile?.listFiles() ?: emptyArray()

    LazyColumn {
        items(files) { file ->
            Text(text = "${if (file.isDirectory) "📁" else "📄"} ${file.name}")
        }
    }

}

```
