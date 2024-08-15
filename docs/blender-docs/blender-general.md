# Blender General Notes

## Importing my Custom Py files

- Make or have a directory where all your **script or re-usable script** will be called from.
- Create a `module`sub folder in the script directory. This is where you place your custom module python files

 Add the directory of your script to your to Blender 
    - `*Preference > file Path > Script Directory*`
  ![alt text](<img/Screenshot 2024-08-12 194423.png>)
    - **Restart your blender** for it to update
  
  Now you can Import your own custom module like in normal python:



```py

import bpy

# located in modules sub directory
import abcd 
import xt_bl_utils
from UtilityFunc import select_edit_bones


print(list(select_edit_bones('LEG')))

xt_bl_utils.deleteAll()
bpy.ops.mesh.primitive_cylinder_add(radius=5)

```

## General Wide search in blender

F3 - shortcut to search all blender (viewport)

## Make an App Template

Generally your current startup file `startup.blend` and `userpref.blend` is stored in:  

`{%AppData%}\Blender Foundation\Blender\4.0\config`  

![config location](img/Screenshot%202024-03-02%20050142.png)

And the system template files is stored in:  
`C:\Program Files\Blender Foundation\Blender 4.0\4.0\scripts\startup\bl_app_templates_system`

But your own custom template files will be stored in:  
`{%AppData%}Blender Foundation\Blender\4.0\scripts\startup\bl_app_templates_user` 

* First in side your `{%AppData%}Blender Foundation\Blender\4.0` directory create `\scripts\startup\bl_app_templates_user`
* Create a folder inside `bl_app_templates_user` with same name as your template name . I will use `xtr_template`
* After customizing your file is to save on do `file > Defaults > Save Start Up` or Just save the file, copy, and paste it in `xtr_template` and rename the blend file to `startup.blend` then you are good to go.
  