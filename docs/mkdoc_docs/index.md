# Intro to Mkdocs

## Getting Started with Mkdocs

1. Download and Install *python 3* and *Visual Studio Code* (if unavailable on your computer)

2. Create a directory for your mkdoc website
      - e.g. *my_story_doc* directory
      - Select your directory and *Right click > open in terminal* and Open the directory in vscode using command `code .`
      - Or Just Right click on folder, got to *Show more option > open with Code*

3. Launch a Mkdocs template in your directory.
      - Go to *terminal (tab) > new terminal*  or *CTRL + SHIFT + `* 
      - In your terminal, Install mkdocs using `pip install mkdocs-material` \(`pip` is python package manager install by default in python 3.4 and above)
      - Create a new site using `mkdocs new .`
  
  Basically You get the following commands:
  
For full documentation visit [mkdocs.org](https://www.mkdocs.org).

### Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.

## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.
   

