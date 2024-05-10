# Blender General Notes

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
  