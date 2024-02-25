# Blender Scripting

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
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_by_type(type=item)
```

here item can take any of the following values:

```py
[‘MESH’, ‘CURVE’, ‘SURFACE’, ‘META’, ‘FONT’, ‘HAIR’, ‘POINTCLOUD’, ‘VOLUME’, 
‘GPENCIL’, ‘ARMATURE’, ‘LATTICE’, ‘EMPTY’, ‘LIGHT’, ‘LIGHT_PROBE’, ‘CAMERA’, ‘SPEAKER’]
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