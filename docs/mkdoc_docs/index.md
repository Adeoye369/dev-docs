# Intro to Mkdocs

## Getting Started with Mkdocs

1. Download and Install *python 3* and *Visual Studio Code* (if unavailable on your computer)

2. Create a directory for your mkdoc website
      - e.g. *my_story_doc* directory
      - Select your directory and *Right click > open in terminal* and Open the directory in vscode using command `code .`
      - Or Just Right click on folder, got to *Show more option > open with Code*

3. Launch a Mkdocs template in your directory.
      - Go to *terminal (tab) > new terminal*  or *CTRL + SHIFT + `*
      - In your terminal, Install mkdocs using `pip install mkdocs` \(`pip` is python package manager install by default in python 3.4 and above)
      (NOTE : You will to add the Python script *C:\..\pythoncore-3.14-64\Scripts* Directory into your `ENVIRONMENT PATH` for mkdocs command to work)
      - You will mostly need to install the following plugins:
        - Mkdocs Material - `pip install mkdocs-material`
        - Mkdocs Awesome pages - `pip install mkdocs-awesome-pages-plugin`

!!! note
    Remember to add `awesome-pages` in your `mkdocs.yml`
      ```yaml
      plugins:
        - search
        - awesome-pages
      ```

  - Create a new site using `mkdocs new .`

  
  Basically You get the following commands:
  
For full documentation visit [mkdocs.org](https://www.mkdocs.org).

### Commands

- `mkdocs new [dir-name]` - Create a new project.
- `mkdocs serve` - Start the live-reloading docs server.
- `mkdocs build` - Build the documentation site.
- `mkdocs -h` - Print help message and exit.

## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.

## Deploying to the web on github.io

In your root directory, create a *.github/workflows/ci.yml* directory
and add the following `yml` code

```bash

name: ci 
on:
  push:
    branches:
      - master 
      - main
permissions:
  contents: write
jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Configure Git Credentials
        run: |
          git config user.name github-actions[bot]
          git config user.email 41898282+github-actions[bot]@users.noreply.github.com
      - uses: actions/setup-python@v5
        with:
          python-version: 3.x
      - run: echo "cache_id=$(date --utc '+%V')" >> $GITHUB_ENV 
      - uses: actions/cache@v4
        with:
          key: mkdocs-material-${{ env.cache_id }}
          path: .cache
          restore-keys: |
            mkdocs-material-
      - run: pip install mkdocs-material 
      - run: mkdocs gh-deploy --force
```

- Go ahead and `git add .` and then `git commit -m "...."`
- Then `git push origin main` push it to main branch

In your github go to *action tab*, under it you see *settings* side nav, select .. gh-pages

## Using Admonitions 

You can create notes, warnings, and success blocks in MkDocs by using *Admonitions* with three exclamation marks (!!!) followed by the block type.

### 1. Enable the Extension

First, add the extension to your ```mkdocs.yml``` configuration file:

```yaml
markdown_extensions:
  - admonition
  - pymdownx.details # Optional: for collapsible blocks
  - pymdownx.superfences # Optional: for nested content

```

### 2. Basic Syntax

```markdown
!!! note
    This is a standard note block.

!!! warning
    This is a warning block for important cautions.

!!! success
    This is a success block for successful outcomes.
```

!!! warning
    Make sure the `!!! <admonition>` starts the beginning of the line (no spaces or tab) or else it won't work.
    For it content, make sure its tabs starts exact a beginning of the admonition text for it to properly recognize 
    it belongs under it.


### 3. Common Types

- Note : `!!! note (general information)`
- Warning: `!!! warning (important cautions)`
- Success: `!!! success (successful outcomes)`
- Tip: `!!! tip (helpful hints)`
- Danger: `!!! danger (critical warnings)`

### 4. Custom Titles
You can change or remove the default title by adding text in quotes:

```markdown
!!! warning "Custom Warning Title"
    Be careful with this specific step.

!!! note ""
    This block has no title at all.

```

## Setting Up Auto Create Image Directory for Mkdocs

- Open your project's *settings.json* file (press `Ctrl+`, or `Cmd+,`, then click the Open Settings (JSON) icon in the top right)
- Add the `markdown.copyFiles.destination` rule to point your images to your docs image folder (e.g., `docs/img`)

```json
{
  "markdown.copyFiles.destination": {
    "**/*.md": "img/"
  }
}
```
alternatively

```json
    "markdown.copyFiles.destination": {
        "**/*.md": "${fileExtName}/${fileName}"
    }

     "markdown.copyFiles.destination": {
        "**/*.md": "${fileExtName}/${documentDirName}_${fileName}"
    }
```


!!! note
    `**/*.md` means whichever markdown directory & file you are in,  an *img* folder is created if not already exist and paste copyfiled img inside

