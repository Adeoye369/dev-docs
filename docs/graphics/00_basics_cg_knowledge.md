# Basic Knowledge for Computer Graphics 


## Calculating Delta Time

```cpp

//       ct = getTime()
//  dt = ct - lt
//  lt = ct
float deltaTime{}, lastTime{};
. . .
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
```

