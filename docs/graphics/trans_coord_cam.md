
# Transformation, Coordinate system and Camera System

```cpp
// Getting screen mouse position from glfw
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    std::cout << "xPos = " << xPos << ", yPos = " << yPos << "\n";
```

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