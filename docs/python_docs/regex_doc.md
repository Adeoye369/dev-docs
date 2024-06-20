# Regular Expression in python

## Regex Basics

```py
import re

str1 = 'this is the first no 454-333-2344 the second is 545-000-1234'
str2 = 'There is no phone number here 0982433-343'

phone_re = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')

# for the first string
n = phone_re.search(str1)
if n : print("Phone(s) found in str1 : ", n.group()) 

n = phone_re.search(str2) # returns None if empty
if n : print("Phone(s) found in str2: ", n.group() )

# OUTPUT:
# Phone(s) found in str1 :  454-333-2344
# Pattern not found
```

Note that when use `[re_comp].search()` the `[res].group()` returns the first match.

if you want to return multiple matches, you will have to use `[re_comp].findall()` this will return a list instead.

### Grouping Expressions

You can divide your regex into different parts. for instance you want to seperate the country code from the phone number.

```py
str1 = 'this is the first no +454-333-2344 the second is'

phone_re = re.compile(r'(\+\d\d\d)-(\d\d\d-\d\d\d\d)')

# for the first string
n = phone_re.search(str1)
if n : print("code = ", n.group(1),", Phone = ", n.group(2))

#OUTPUT:
# country code =  +454 , Phone =  333-2344
```

### Match Zero or More with Star

```py
>>> import re
>>> suprex = re.compile(r'Super(wo)*man')
>>> o1 = suprex.search("The Superman's adventure") 
>>> o1.group()
'Superman'

>>> o2 = suprex.search("The Superwomans adventure")
>>> o2.group()
'Superwoman'

>>> o2 = suprex.search("The Superwowowowowomans adventure")   
>>> o2.group()
'Superwowowowowoman'

```

### Match one or more with the Plus

```py
>>> suprex = re.compile(r'Super(wo)+man') 
>>> o2 = suprex.search("The Superwowowowowomans adventure")
>>> o2.group()
'Superwowowowowoman'

>>> o2 = suprex.search("The Supermans adventure")           
>>> o2 == None
True

```

If there are one or more pattern in group `(wo)` in the string. If at least one is not available it returns `None`

### Match Specific Repitions with Braces

so if you have `(do){3}` will match `dododo` and nothing more or less

```py
>>> rex1 = re.compile(r'(do){3}')               
>>> o = rex1.search('This is the dododo pizza') 
>>> o.group()
'dododo'

>>> o = rex1.search('This is the dodo pizza') 
>>> # Result: None
```

### Greedy or Non-greedy Matching

if you write `(do){2, 4}` it will match two, three or four instance of pattern

```py
>>> rex1 = re.compile(r'(do){2,4}') 
>>> o = rex1.search('This is the dododododo pizza') 
>>> o.group()
'dodododo'
```

You might wonder why not retrieve the first two `dodo` istead of four `dodododo`. The reason being by default, python regex is *greedy* i.e it will retrieve the highest pattern. for it to be non greedy we use the `?`

```py
>>> rex1 = re.compile(r'(do){2,4}?') # NON-GREEDY
>>> o = rex1.search('This is the dododododo pizza')
>>> o.group()
'dodo'
```

| pattern code | Description|
|--------------|-------------|
| `Bat(wo)?man`| ? means the `(wo)` is optional so in regex like `Super(wo)?man`, it will find `Superman` but if no `Superwoman`   | 
| `Bat(wo)*man`| select zero or more `(wo)` in `Bat Batman Batwowowoman` select in order of arrangement |
|`'Super\w+'`| Select one or more words after `Super` select `['Superwoman', 'Superman', 'Superdog', 'Supergirl']`|