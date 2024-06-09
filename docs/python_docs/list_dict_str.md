# List, Dictionary and Strings

A *List* collection of values of same data types (float, int, string even list itself) that starts with a `[` and end with `]`.

You getting value from List with indexes

```python
animal = ['dog', 'cat', 'chicken']

# access index
animal[0] # dog
animal[2] # chicken
```

if you attempt to get the value beyond the list index say `animal[100]` in get an IndexError.

List can contain other list :

```python
# Example of a 3-tensor list
mat =[  
        [
            [22, -11, 34],
            [41, 0, -9],
            [23, 1, 1]
        ]
    ,
        [
            [22, -11, 34],
            [41, 0, -9],
            [23, 1, 1]
        ]
 
    ]

# looping through
item = []
for i in mat:
    for j in i:
        for k in j: 
            item.append(k)

# printing in different levels of indexes
print(mat[1]) 
print(mat[0][2])
print(mat[1][0][2])

```
