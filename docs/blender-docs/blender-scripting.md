# Blender Scripting

## Making blender work on Vscode

For Vscode to be able to read blender codes

```bash
pip install fake-bpy-module-latest
```

this provides all the necessary bpy module-like

- Then install this extension on vscode extension:
![alt text](img/image-3.png)

- CTRL + SH + P - blender : start
  incase you run into an error, do the follow

  goto your directory where blender python is installed:
    `C:\Program Files\Blender Foundation\Blender 4.2\4.2\python`
  - R+CLK - `properties > security`
  - Under (group or user) scrolled down to `User` and click `Edit` button
  - check the option to `write` then ok it

![alt text](img/image-4.png)

## Getting Started with blender Addons

minimum file structure

```bash

my_extension-0.0.1.zip
├─ __init__.py
├─ blender_manifest.toml
└─ (...)

```


## Blender Generic basics

### Listing all Active objects (DATA)

```py
for n in bpy.data.objects:
    n.name, n.type, n.__class__.__name__
'''
('Camera', 'CAMERA', 'Object')
('Cylinder', 'MESH', 'Object')
('Icosphere', 'MESH', 'Object')
('Light', 'LIGHT', 'Object')
'''
```

### Select all Active objects (OPS)

```py
# action param: TOGGLE, SELECT, DESELECT, INVERT
bpy.ops.object.select_all(action='DESELECT')

```

here item can take any of the following values:

```py
# item param: [‘MESH’, ‘CURVE’, ‘SURFACE’, ‘META’, ‘FONT’, ‘HAIR’, ‘POINTCLOUD’, ‘VOLUME’, 
# ‘GPENCIL’, ‘ARMATURE’, ‘LATTICE’, ‘EMPTY’, ‘LIGHT’, ‘LIGHT_PROBE’, ‘CAMERA’, ‘SPEAKER’]
bpy.ops.object.select_by_type(type=item)
```

### Remove Objects' Meshs(DATA)

```py
for n in bpy.data.objects:
    if n.type == 'MESH':
        bpy.data.objects.remove(n)
```

### Remove all Active  select (OPS)

```py
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete()
```

### Listing all Active Material nodes

```py
for n in bpy.data.materials[1].node_tree.nodes:
    n.name, n.type, n.__class__.__name__

'''
('Principled BSDF', 'BSDF_PRINCIPLED', 'ShaderNodeBsdfPrincipled')
('Material Output', 'OUTPUT_MATERIAL', 'ShaderNodeOutputMaterial')
'''
```

### Select Active Objects

```py
 bpy.context.active_object
# >> bpy.data.objects['Cylinder']

bpy.context.active_object
# >> bpy.data.objects['Icosphere']
```

### Delete active object(s)

```py
 bpy.ops.object.delete()
 # {'FINISHED'}

 ```

## creating a new material from blender

```py title="demo"
# CREATE a new material
mat1 = bpy.data.materials.new (name = "MatBasic")

# ACCESS individual material id or by name
bpy.data.materials[0]   
bpy.data.materials["MAT_01"] 

# CREATE a ndoe type  using 
mat1.node_tree.nodes.new(type="ShaderNodeBsdfDiffuse")

# ACCESS material nodes by index or by name
mat1.node_tree.nodes[0] # "Material Output"
mat1.node_tree.nodes["Diffuse BSDF.001"]
```

## Create a Simple Icosphere Principled BDSF applied

```py
import random

def createNewMaterial():
    # create a new material
    mat = bpy.data.materials.new(name = "MatA")
    # enable the created material
    mat.use_nodes = True

    # mat1.node_tree.nodes.new(type="ShaderNodeBsdfDiffuse")

    prinBSDF = mat.node_tree.nodes['Principled BSDF']
    # Set the color of the material
    prinBSDF.inputs["Base Color"].default_value = (0.1, 0.2, 0.3, 1)
    # set the roughness 
    prinBSDF.inputs["Roughness"].default_value = 0.3
    # set the metallic
      prinBSDF.inputs["Metallic"].default_value = random.uniform(0.1, 1.0)

    return mat


''' Creating an Icosphere and apply material '''
def createIcoSphere():
    # create an icosphere and shade smooth it
    bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=3)
    bpy.ops.object.shade_smooth()

    # Get the active object i.e icosphere
    active_object = bpy.context.active_object
    # Add the material to the object material list
    ico_mat = createNewMaterial()
    active_object.data.materials.append(ico_mat)
    
createIcoSphere()
```

## Helper function : DelectAll item

This function will Select and delete all item specified as `item`
if not specified, all selected objects in the scene will be deleted.

```py
'''
Function to Select and delete all selected item specified
if not specified, delete all selected
item can be:
['MESH', 'CURVE', 'SURFACE', 'META', 'FONT', 'HAIR', 'POINTCLOUD', 'VOLUME', 
'GPENCIL', 'ARMATURE', 'LATTICE', 'EMPTY', 'LIGHT', 'LIGHT_PROBE', 'CAMERA', 'SPEAKER']
'''
def deleteAll(item = None):
    
    if (item == None):
        # select all objects
        bpy.ops.object.select_all(action='SELECT')
    else:
        # select all by item type
        bpy.ops.object.select_all(action='DESELECT')
        bpy.ops.object.select_by_type(type=item)

    # delete all selected
    bpy.ops.object.delete()

    # Delete unused materials
    bpy.ops.outliner.orphans_purge(do_local_ids=True, do_linked_ids=True, do_recursive=True)

```


### Adding and Removing material from object

```py
# cube = bpy.context.active_object
cube.data.materials.append(ico_mat) # Adding material to object
cube.data.materials.pop(index=0) # Removing material at index
cube.active_material_index #get/set index material
```

## BLENDER REFERENCE

### Node internals

**NodeInternal(Node)**
base classes — bpy_struct, Node  

subclasses — `CompositorNode`, `FunctionNode`, `GeometryNode`, `NodeFrame`, `NodeGroup`, `NodeGroupInput`, `NodeGroupOutput`,` NodeReroute`, `ShaderNode`, `TextureNode`

[https://docs.blender.org/api/current/bpy.types.NodeInternal.html#bpy.types.NodeInternal](https://docs.blender.org/api/current/bpy.types.NodeInternal.html#bpy.types.NodeInternal
)

### Creating a new Node Frame

```py
frame = mat1.node_tree.nodes.new(type="NodeFrame") # New Node frame
glass = mat1.node_tree.nodes.new(type='ShaderNodeBsdfGlass')
trans = mat1.node_tree.nodes.new(type='ShaderNodeBsdfTransparent')
# Adding the node Frame to Nodes
glass.parent = frame
trans.parent = frame

# Slightly different for node group
group = mat1.node_tree.nodes.new(type='ShaderNodeGroup')
group.node_tree = bpy.data.node_groups.new("A Group", "ShaderNodeTree") # New Node
group.node_tree = bpy.data.node_groups["NodeGroup"] # already existing

```

list of shader Nodes  
[https://docs.blender.org/api/current/bpy.types.ShaderNode.html](https://docs.blender.org/api/current/bpy.types.ShaderNode.html)

### Creating a Node Group(globally)

```py
bpy.data.node_groups.new("A Group", "ShaderNodeTree")
# bpy.data.node_groups['A Group']

D.node_groups.new(name = "A Group", type ="ShaderNodeTree")
# bpy.data.node_groups['A Group.001']
```

### Group Node Sample

```py
import bpy

# create a group
test_group = bpy.data.node_groups.new(name='testGroup', type='ShaderNodeTree')

# create group inputs
group_inputs = test_group.nodes.new('NodeGroupInput')
group_inputs.location = (-350,0)
test_group.inputs.new('NodeSocketFloat','in_to_greater')
test_group.inputs.new('NodeSocketFloat','in_to_less')

# create group outputs
group_outputs = test_group.nodes.new('NodeGroupOutput')
group_outputs.location = (300,0)
test_group.outputs.new('NodeSocketFloat','out_result')

# create three math nodes in a group
node_add = test_group.nodes.new('ShaderNodeMath')
node_add.operation = 'ADD'
node_add.location = (100,0)

node_greater = test_group.nodes.new('ShaderNodeMath')
node_greater.operation = 'GREATER_THAN'
node_greater.label = 'greater'
node_greater.location = (-100,100)

node_less = test_group.nodes.new('ShaderNodeMath')
node_less.operation = 'LESS_THAN'
node_less.label = 'less'
node_less.location = (-100,-100)

# link nodes together
test_group.links.new(node_add.inputs[0], node_greater.outputs[0])
test_group.links.new(node_add.inputs[1], node_less.outputs[0])

# link inputs
test_group.links.new(group_inputs.outputs['in_to_greater'], node_greater.inputs[0])
test_group.links.new(group_inputs.outputs['in_to_less'], node_less.inputs[0])

#link output
test_group.links.new(node_add.outputs[0], group_outputs.inputs['out_result'])


```

## BASIC OPERATORS CLASS FOR OPENING FILE

```py
import bpy
import os

from bpy.props import StringProperty, BoolProperty
from bpy_extras.io_utils import ImportHelper
from bpy.types import Operator


class VIEW_OT_TestOpenFileBrowser(Operator, ImportHelper):

    bl_idname = "image.open_filebrowser"
    bl_label="Open the file browser"

    # Filter the type of selected file
    filter_glob : StringProperty( default="*.jpg; *jpeg;*.png; *.tif, *.tiff",
                                 options={'HIDDEN'}) 
    
    # Add properties to the file browser window menu
    test_boolean: BoolProperty(name="Check to test", 
                               description="The description to check the something",
                                default=True) 

    
    def execute(self, context):
        "Do something with selected file"
        
        filename, extension = os.path.splitext(self.filepath)
        print('Selected file = ', self.filepath)
        print('File name = ', filename)
        print('File Extension = ', extension)
        
        return {'FINISHED'}




def register():
    bpy.utils.register_class(VIEW_OT_TestOpenFileBrowser)

def unregister():
    bpy.utils.unregister_class(VIEW_OT_TestOpenFileBrowser)

if __name__ == "__main__":
    register()
```

Go to your view 3d press `F3` and type the name in the `bl_idname`
in our case `image.open_filebrowser`

You will have

![alt text](<img/Screenshot 2024-08-13 183337.png>)

You will get a file browser file like so:

![u](<img/Screenshot 2024-08-13 183727.png>)


## IMPORT TEXTURE IMAGE AS RIG WORKFLOW

### 1. Custom image as plane

This is a slightly modified to allow our workflow

```py


import bpy


def custom_img_as_plane(image_name, image_dir):
    
    # Import image as mesh plane operator
    bpy.ops.image.import_as_mesh_planes( directory=image_dir, 
                                        filepath=f"{image_dir}{image_name}",
                                        files=[{"name":image_name, "name":image_name}],  
                                        image_sequence=True,relative=False,align_axis='+X')
    
    # Change material Image Texture node to work for animation seq.
    bpy.data.images[image_name].source = 'SEQUENCE'

    image_name_only = image_name.split('.')[0] # split e.g "seq-01.jpg" into ['seq-01', 'jpg'] 
    bpy.data.materials[image_name_only].node_tree.nodes["Image Texture"].image_user.frame_offset = 1


files_data = {
    "sq_00.jpg" : "C:/Projects/Blender/_SandBox/seq1/",
    "eye_01.png" : "C:/Projects/Blender/_SandBox/eye_imgs/"
}

for k, v in files_data.items():
    print(k, v)
    custom_img_as_plane(k, v)

```