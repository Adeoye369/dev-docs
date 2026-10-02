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

## The findall() Method

`findall()` returns the strings of ***every*** match in the search string. This is returned as a list

```py
>>> rex1 = re.compile(r'Super\w{3,5}') 
>>> rex1.findall('The new  Superwoman, Superman, Superdog and Supergirl')

['Superwoman', 'Superman', 'Superdog', 'Supergirl']
```

If there are groups in the regex, the method will return a list of tuple

```py
>>> rex1 = re.compile(r'(Super\w)(\w+)')  
>>> rex1.findall('The new  Superwoman, Superman, Superdog and Supergirl')

[('Superw', 'oman'), ('Superm', 'an'), ('Superd', 'og'), ('Superg', 'irl')]

```

## Making our own character class

There might be times when you just what to match a set of characters say just vowels, say first 5 alphabet or maybe just some numbers and the default character classes a too broad. You can use the square bracket.


|Regex Character class | Description|
|----------------------|-------------|
|`\d`| Any numeric digit from 0 to 9 same as `(0|1|2|3|4|5|6|7|8|9)` or `[0-9]`|
|`\D`| Any that is *not* a Numeric from 0 to 9|
|`\w`| Any letter, numeric digit or the underscore(matching "word")|
|`\W`| Any *not* "Word"|
|`\s`| matching space, tab, newline characters|
|`\S`|matching *not* space|

Example to demonstrate character class usage:

```py
>>> import re
>>> xregx = re.compile(r'\d+\s\w+')
>>> xregx.findall('12 drummers, 11 pipers, 10 lords, 9 ladies, 8 maids) 

['12 drummers', '11 pipers', '10 lords', '9 ladies', '8 maids'  ]
```

```py
>>> crex = re.compile(r'b[a-fA-F]+s') # [abcdefABCDEF]
>>> crex.findall("The bacs and the bades is fading abacs not aback bees are beads or beefs") 

['bacs', 'bades', 'bacs', 'bees', 'beads', 'beefs']
```
The carets character negate the selection

```py
>>> crex = re.compile(r'b[^a-f]+s')                                                                      
>>> crex.findall("The bacs boys bxings and blins and the bades is fading abacs not aback")
['boys', 'bxings', 'blins']
```

## BeginWith(^) and EndWith($) sign characters

You can specify a match most occur at the begin of a search text with (^) e.g.
`r'^Ade'` this match `Adeoye is going home` any string start with the match. Similarly ($) match at the end of any searched text e.g. `r'\d$'` match `the fure is 2112` ending with a number.


```py
>>> beginWithRegex = re.compile(r'^Ade') 
>>> o = beginWithRegex.search('Adeoye  but omoAde or Ade#1234') 
>>> o.group()

'Ade'

>>> o = beginWithRegex.search('Is also Adegbite, but omoAde')        
>>> o == None

True
```

Similarly demonstrating endswith

```py
>>> endWithRegex = re.compile(r'\d$')
>>> o = endWithRegex.search('Adeoye  but omoAde or Ade#1234') 
>>> o.group()

'4'
```

Combining the two characters

```py
>>> wholeStringIsNum = re.compile(r'^\d+$') 
>>> o = wholeStringIsNum.search('0814889453332') 
>>> o.group()

'0814889453332'

>>> o = wholeStringIsNum.search('0814adef445332')
>>> o==None

True
```

!!! Note " Caret (^) Usage"
    Caret has two use, first inside character class negation `[^aeiou]` *Not* vowel in this case. It can also be use as match begin-with as we have seen above

## the wildcard character

the *dot*(.) is consider a wildcard character as it can be use the represent any character, be it text, number or special character in a string. The only exception is space, newline or tab.

```py
>>> anRegex = re.compile(r'.an') 
>>> anRegex.findall("He ran to the  can in the car but ban in a tan in a 2an %an /an whan? ") 

['ran', 'can', 'ban', 'tan', '2an', '%an', '/an', 'han']
```

### Matching Everything with a Dot-Star

what (.*) does is match literal everything.

```py
>>> nameRegex = re.compile(r'First Name: (.*) Last Name: (.*)')                                          
>>> names = nameRegex.search("First Name: Kinokola Last Name: Omotayo") 
>>> names.groups()

('Kinokola', 'Omotayo')
>>>
```

The dot star by default uses the greedy mode by default. To use the non-greedy mode, use `(.*?)` instead.

```py
nonGreedyRex = re.compile(r'<.*?>')
>>> mo = nonGreedyRex.search("<To serve> or <Not to serve>") 
>>> mo.group()

'<To serve>'
                       
>>> greedyRex = re.compile(r'<.*>')  
>>> mo = greedyRex.search("<To serve> or <Not to serve>")    
>>> mo.group()

'<To serve> or <Not to serve>'

>>> notgreedyRex = re.compile(r'<.*?>') 
>>> mo = notgreedyRex.findall("<To serve> or <Not to serve>")    
>>> mo

['<To serve>', '<Not to serve>']

```

## Regex Code Table

| pattern code | Description|
|--------------|-------------|
|`\d`| Any numeric digit from 0 to 9 same as `(0|1|2|3|4|5|6|7|8|9)` or `[0-9]`|
|`\D`| Any that is *not* a Numeric from 0 to 9|
|`\w`| Any letter, numeric digit or the underscore(matching "word")|
|`\W`| Any *not* "Word"|
|`\s`| matching space, tab, newline characters|
|`\S`|matching *not* space|
|`^`| a match most occur at the begin of a search text .`r'^Ade'` this match `Adeoye is going home` |
|`$`| A match most occur at the end of  searched text e.g. `r'\d$'` match `the fure is 2112` |
|`[0-5]`| this a shorten numeric character class for `(0|1|2|3|4|5)`or `[012345]`|
|`[a-zA-Z0-9]`| a letter  will match all lower, upper letters and numbers you can use `\w` instead|
|`[^a-z]`| placing the caret charater (^) means you are negating your class|
|`^\d+$`| string must contain all numbers|
| `Bat(wo)?man`| ? means the `(wo)` is optional so in regex like `Super(wo)?man`, it will find `Superman` but if no `Superwoman`   | 
| `Bat(wo)*man`| select zero or more `(wo)` in `Bat Batman Batwowowoman` select in order of arrangement |
|`'Super\w+'`| Select one or more words after `Super` select `['Superwoman', 'Superman', 'Superdog', 'Supergirl']`|