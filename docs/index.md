# AI learning Docs

## Matplob lib

Intro to matplot library

## Installation without Anaconda

I Will recommend installing anaconda, I will save you a lot of hassle late on.
Installation involve first creating a virtual environment.

Create a file `main.py`

```py

import matplotlib.pyplot as plt
import numpy as np

# Generate some linear data
x = np.linspace(0, 10, 500)
# y = np.sin(x) # calc. sine-wave of each
y = np.exp2(x- 3)- 5*x - 11

# Create a line plot
plt.plot(x, y, label='Sine Function')
plt.show()
```

create a new virtual environment by opening the terminal,

```bash
>> python -m venv env1 # env1 is the dir name
>> ./env1/Scripts/activate
```

If you are running it for the first time, You will probably encounter an error. So go to your Powershell run as Adminstrator

```cmd
Set-ExecutionPolicy Unrestricted
```

Once you have done that a virtual environ of this structure is created
![alt text](./ai-dev-docs/img/image.png)

## Plotting Multiple Graph in one plot

```python
t = np.linspace(-10, 50, 50)

# distance covered by A
yA = 2 * t - 1

# distance covered by B
yB = t + 2

fig, ax = plt.subplots()
plt.title("Graph of yA and yB distance over time")
plt.axhline(y=0, c='lightgray')
plt.axvline(x=0 , c='lightgray')

ax.set_xlim([-10, 20])
ax.set_ylim([-10, 20])

ax.plot( t,yA, c='blue', label="y = 2t - 1")
ax.plot( t,yB, c='purple')

plt.axhline(y=5, c='green', linestyle='--', linewidth='0.5')
plt.axvline(x=3, c="green", linestyle='--', linewidth='0.5')
```