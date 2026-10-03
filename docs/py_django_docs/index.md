# Getting Started with Django

## Install python on your machine

-  Ensure that python is properly installed

## Creating First Django Project 

!!! note
    This part is following [tutorial from official django](https://docs.djangoproject.com/en/6.1/intro/tutorial01/) page
        
In directory you want to work in run the following command:

```powershell
    django-admin startproject prodman djangotutorial
```

Let’s look at what startproject created:

```
djangotutorial/
    manage.py
    prodman/
        __init__.py
        settings.py
        urls.py
        asgi.py
        wsgi.py

```

- Run `python manage.py runserver`  and ignore any warning about migration etc,
You will have access to launch from a port `http://127.0.0.1:8000/`

![alt text](img/magatD8BiQ.png)


!!! note
    In the Python Django shell, the equivalent of JavaScript's .includes() is the __contains or __icontains field lookup.
    To filter your query, you should use Question.objects.filter(question_text__icontains="you").
    The Differences
    * __icontains (Recommended): This is case-insensitive. It will match "you", "You", "YOU", etc.
    * __contains: This is case-sensitive. It will only match the exact lowercase string "you".

    ```py
    Question.objects.filter(question_text__icontains="you") 
    # <QuerySet [<Question: question: How old are you, pub. date: 2026-10-03 08:58:29.241040+00:00
    ```


### Error Fixing 

The error happens because `get()` can only return exactly one object. 
Since there are 2 Question objects published in your `current_year`, Django throws a *`MultipleObjectsReturned` exception.*
Depending on what you actually want to do with those two questions, you have a few ways to fix this:

**Option 1: Keep all matching records**
If you want to look at or loop through all the questions published this year, swap `.get()` for `.filter()`.

```py
# Returns a QuerySet containing all matching questions
questions = Question.objects.filter(published_date__year=current_year)

```

**Option 2: Get only the very first or latest record**
If you only care about one specific question out of the duplicates, combine `.filter()` with `.first()` or `.last()`. This will safely return a single object (or None if none exist) without crashing.

```py
# Gets the oldest one created this year
first_question = Question.objects.filter(published_date__year=current_year).first()

# Gets the newest one created this year (if ordered by date)
latest_question = Question.objects.filter(published_date__year=current_year).latest('published_date')

```

**Option 3: Narrow down your search**
If you truly only wanted one specific question, your search criteria is too broad. Add more specific fields inside `.get()` to pinpoint the exact row.

```py
# Narrowing down by adding another unique field like title or id
question = Question.objects.get(published_date__year=current_year, id=1)

```

```py
>>> ChoiceSelection.objects.filter(question__published_date__year=current_year)

# Delete a choiceselection
>>> c = q2.choiceselection_set.filter(choice_text__icontains="Nacking")
>>> c.delete()
# (1, {'poll.ChoiceSelection': 1})

>>> q2.choiceselection_set.all()
# <QuerySet [
#   <ChoiceSelection: choice: Not Much votes: 0>, 
#   <ChoiceSelection: choice: Too Much votes: 0>, 
#   <ChoiceSelection: choice: the Sky votes: 0>,
# ]>
```


