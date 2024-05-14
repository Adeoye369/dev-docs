# Welcome to Adeoyes Dev Docs

This is mee working to MKDocs document

## CPP Basics

### The `std::arrays`  and `std::vector`

```c++
float ages4[9]{ 1.0 };
float ages5[9] = { 2.0f, 4.4f,5.0, 5 };

std::array<std::string, 10> ages1{"34", "3"}; // brakect init: fills remain with empty string
std::array<int, 10> ages2 = {3, 4, 3}; // Equals init:  the first 3/10 elements init with equals
std::array<float, 5> ages3 {}; // init all value to 0.0

std::vector<int> age6(5, 3.5f); // fill all 5 init elements with 3.5f
std::vector<int> age7{ 3, 5, 6 }; // bracket init:  with 3 elements 
std::vector<int> age8 = { 13, 15, 26, 5, 11 }; //Equals init: fills with 5 element 
std::vector<int> ageCopy1 (age6); // copy array

ages1[5] = "39";
ages1[9] = "No";
for (auto &i : ages1)
{
 std::cout << i << " ";
}

```

### The most Basic Multithread Example : Part 1

```cpp

#include <iostream>
#include <thread>
#include <chrono>

void func1(char char1){
 for (size_t i = 0; i < 1000; i++)
  std::cout << char1;
}

void func2() {
 int i = 0;
 while (i < 1000){
  std::cout << "X";
  i++;
 }
}

int main()
{
 std::thread t1{ func1, '0' };
 std::thread t2(func2);

 t1.join();
 t2.join();

 return 0;
}
```

### The Most Basic Multithread Example : Part 2


```cpp

#include <iostream>
#include <map>
#include <thread>
#include <chrono>
#include <string>

using namespace std::chrono_literals;


void refresh_focast(std::map<std::string, float> cityForecast) {

 while (true) {
  std::cout << "===========================\n";
  for (auto& forecast: cityForecast)
  {
   forecast.second++;
   std::cout << "City : " << forecast.first << 
    ", \nTemperature: " << forecast.second << "\n\n";

  }

  std::this_thread::sleep_for(2000ms);
 }
}


int main()
{
 std::map<std::string, float> cityTempList{
  {"Lagos", 24.0f},
  {"Abuja", 15.7f},
  {"Adamawa", 10.0f},
  {"Jos", 2.9f}
 };

 std::thread worker1(refresh_focast, cityTempList);

 worker1.join();

 return 0;
}
```

## Introduction to GL

This is another intro you can have when working with OpenGL.
Compile shader those what it says it compile the shaders and much more

```c++ title="compile-shader.cpp" linenums="30" hl_lines="11 12 13 14"
static unsigned int CompileShader(unsigned int type, const std::string& source) 
{
    GLuint shader_id = glCreateShader(type);

    const char* shader_src = source.c_str();
    glShaderSource(shader_id, 1, &shader_src, nullptr);

    glCompileShader(shader_id);

    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    /* int length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
    char* msg = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(shader_id, length, &length, msg);*/
    if (success == GL_FALSE) {
        char msg[1024];
        glGetShaderInfoLog(shader_id, 1024, NULL, msg);

        std::cout << " VERTEX:  \n" << msg << "\n";
    }
    return shader_id;
}// end CompileShader
```

## Parse Fragment and Vertex Shader

There are various approach to parse your shaders and you can start by creating things like `basic.shader` to serve as your default shader.

* We start by creating a struct to hold the vertex and Fragment shader
  
```c++ linenums
struct ShaderSource {
    std::string VertSource;
    std::string FragSource;
};
```



