# Basics of NodeJs

## Basic Setup - Fixing Execution Error

Their are some situation where `npm` is not functioning due to windows security issue, even though you already have it installed.

FIX:

- Run **Windows Powershell** as an **Admin**

Pass the following code

```sh
# Global wide fix
Set-ExecutionPolicy RemoteSigned

# For Just the Current User
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

Press Y yes, or A yes to All
Then you should be able to run code normally


## Creating a new node app

```sh
# Require you answer follow up quest
>>> npm init 

# Use default info
>>> npm init -yes 

>>> npm install < package_name >
# or 
>>> npm i < package_name >

```

## intro `hello node`

First node code

```js
console.log("Hello node");
```

in console run : `node dir/index.js`


## copying file in node

This will copy the file in our current directory

```js
const fs = require("fs")

fs.copyFileSync("file1.txt", "file2.txt")
```

![alt text](../js_docs/img/image.png)

## Writing to file

```js
import * as fss from 'node:fs'
import fs from 'node:fs/promises'

fss.writeFileSync('somefile.txt', 'TO-DO CONTENT')
fs.writeFile('somefile-async.txt', 'ASYNC-CONTENT', function(err){console.log(err)})
```

!!!Note
        This will create the file if its not already existing

## getting filePath and directory

```js
import path from 'path';
import {fileURLToPath} from 'url';

// absolute path to filename, get the directory name 
const file_name = fileURLToPath(import.meta.url);
const file_dir= path.dirname(filename);
```

## Working with path.resolve()

```js
const path = require('path');

// Example 1: Resolving to an absolute path
console.log(path.resolve('/foo', '/bar', 'baz')); // Output: /bar/baz (on Unix-like) or C:\bar\baz (on Windows)

// Example 2: Using a relative path and current working directory
// Assuming current working directory is C:/user/myproject
console.log(path.resolve('src', 'components', 'button.js')); 
// Output: C:/user/myproject/src/components/button.js (on Unix-like)

// Example 3: Resolving with '..'
console.log(path.resolve('/foo/bar', '../baz')); 
// Output: /foo/baz (on Unix-like)
```

### Usage in webdev?

```js
import { fileURLToPath } from 'url';
import path from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const appRoot = path.resolve(__dirname, '..', '..'); // Adjust '..' based on your file's depth
console.log('Application Root:', appRoot);
```

## Resolve Vs Path

**Absolute vs. Relative:**

`path.resolve()` always returns an absolute path, while `path.join()` returns a path that can be either absolute or relative, depending on the input segments.

**Resolution Logic:**

`path.resolve()` uses a right-to-left resolution process that considers absolute path segments and the current working directory, whereas `path.join() `simply concatenates and
normalizes segments.

## Creating A Folder Recursively

```js
const fs = require('node:fs/promises');

async function createDir(dirPath) {
  try {
    // Automatically checks and creates the directory if missing
    await fs.mkdir(dirPath, { recursive: true });
    console.log('Directory is ready');
  } catch (err) {
    console.error('Error creating directory:', err.message);
  }
}

createDir('./my-new-folder/sub-folder');

```

### Works only for one Folder level

```js
const fs = require('node:fs/promises');

async function createDirIfNew(dirPath) {
  try {
    await fs.mkdir(dirPath);
    console.log('Directory created successfully.');
  } catch (err) {
    if (err.code === 'EEXIST') {
      console.log('Notice: Directory already exists.');
    } else {
      console.error('Error creating directory:', err.message);
    }
  }
}

createDirIfNew('./my-folder');

```

### Works for Multiple sub-level

To separate the logic completely, you can create a dedicated `exists()`
helper function using `fs.stat()` that returns a boolean,
and then call it inside your creation function.Here is the clean, separated approach using Async/Await:

```js
const fs = require('node:fs/promises');

/**
 * 1. The Check Function
 * Returns true if the path exists, false if it does not.
 */
async function directoryExists(dirPath) {
  try {
    await fs.stat(dirPath);
    return true; 
  } catch (err) {
    if (err.code === 'ENOENT') {
      return false; 
    }
    throw err; // Rethrow unexpected errors (like permission issues)
  }
}

/**
 * 2. The Create Function
 * Uses the check function to decide whether to create or log.
 */
async function createDir(dirPath) {
  try {
    const exists = await directoryExists(dirPath);

    if (exists) {
      console.log('Notice: Directory already exists.');
      return;
    }

    await fs.mkdir(dirPath, { recursive: true });
    console.log('Directory created successfully.');

  } catch (err) {
    console.error('Operation failed:', err.message);
  }
}

// Example usage:
createDir('./my-separated-folder');
```

## Dynamically upload user Avatar

Below is a complete, scalable setup that reads a userId from the form data and creates a unique directory`(./uploads/user-<id>/)` for that specific user.

```js
import express from 'express';
import multer from 'multer';
import { mkdir } from 'node:fs/promises';
import { join } from 'node:path';

const app = express();

// 1. Configure the dynamic storage engine
const dynamicStorage = multer.diskStorage({
  destination: async (req, file, cb) => {
    // Extract dynamic variables from the request body or parameters
    // Note: Fields must be sent BEFORE files in the frontend FormData
    const userId = req.body.userId || 'guest'; 
    const uploadPath = join(process.cwd(), 'uploads', `user-${userId}`);

    try {
      // Ensure the dynamic directory exists before storing the file
      await mkdir(uploadPath, { recursive: true });
      cb(null, uploadPath); // Pass the path to Multer
    } catch (error) {
      cb(error, null); // Pass any file system errors to Multer
    }
  },
  filename: (req, file, cb) => {
    // Generate a unique filename to prevent overwrites
    const uniqueSuffix = Date.now() + '-' + Math.round(Math.random() * 1E9);
    cb(null, `${uniqueSuffix}-${file.originalname}`);
  }
});

// 2. Initialize the upload middleware
const upload = multer({ storage: dynamicStorage });

// 3. Create the upload route
app.post('/upload', upload.single('avatar'), (req, res) => {
  if (!req.file) {
    return res.status(400).json({ error: 'No file uploaded.' });
  }
  
  res.json({
    message: 'File uploaded successfully!',
    folder: req.file.destination,
    filename: req.file.filename
  });
});

app.listen(3000, () => console.log('Server running on port 3000'));

```

### Important Rule for Frontend Integration

When sending data from your frontend using FormData, the order of the appended fields matters. You must append text fields before files. Otherwise, req.body.userId will be empty inside the destination function.

```js
// Frontend JavaScript example
const formData = new FormData();
formData.append('userId', '4521'); // Append text fields FIRST
formData.append('avatar', fileInput.files[0]); // Append files LAST

fetch('/upload', { method: 'POST', body: formData });

```
