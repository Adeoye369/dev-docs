# Documentation for my Python learning

## basics

Working with basics.
(1.) `input()` and `print()`
(2.) Then we work with the type

```python

from datetime import datetime

name = input('type your name :' )
age = input('My age:')
month = input('month number: ')

months = ['jan', 'feb', 'march', 'apr', 'may', 'jun',\
           'jul', 'Aug','sep', 'oct', 'nov', 'dec']
birth_year = datetime.now().year - int(age)

print("my name is {0} and I was born in month of {1} in the year {2}"\
      .format(name, months[int(month) - 1], birth_year))
```
![print for the code above](img/image.png)

### Working with string format

simple string format, put `f'{content of string}`.

```python
game_name = 'Alphalt 9'
user_name = 'Adeoye'
str1 = f"My name is {user_name}, best game -> {game_name}"

print(str1)
```

Some more python basic string function examples

```python
method_name = "The method name is the name of company"

print(len(method_name))
print(method_name.upper())
print(method_name.lower())
print(method_name.title())

print(method_name.find('name')) # Return the index
print(method_name.replace('name', 'age'))

print('name' in method_name) # Returns true or false
print('school' in method_name)

```
![alt text](img/image-1.png)


Using the format string method.

```python
weight_in_pds = input('What is your weight in pounds: ')

weight_in_kg = int(weight_in_pds) * 0.45359237

print('''if your weight in pd is {0:.3f},your weight in kg is {1:.2f}
      '''.format(int(weight_in_pds),weight_in_kg))
```

### Simple for loop demo

```python title="print F as x"
numbers = [5, 2, 5, 2, 2]

# Works for just py
for x in numbers:
    print('x' * x)

# in case of other lang
  for x in numbers:
    output = ""
    for xi in range(x+1):
        output += 'x'
    print(output)

```
The Result is
![alt text](img/image-2.png)

## List in Python

```python
# Example of a 3-tensor list
mat =[  
    [[22, -11, 34],
    [41, 0, -9],
    [23, 1, 1]]
    ,
    [[22, -11, 34],
    [41, 0, -9],
    [23, 1, 1]]
    ,
    [[122, -11, 4],
    [41, 0, -9],
    [23, 1, 31]]
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
print(mat[2][0][1])



print(item) # list all the item in 3 tensor           
print(set(item)) # remove duplicate in list
```
result:
![alt text](img/image-3.png)