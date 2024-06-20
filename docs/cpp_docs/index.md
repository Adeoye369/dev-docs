
# Introduction to CPP

## CPP Basics

### The `std::arrays`  and `std::vector`

```c++
float ages4[9]{ 1.0 }; // initialize first element and others to zero
float ages5[9] = { 2.0f, 4.4f,5.0, 5 }; // initialize first four elements

std::array<std::string, 10> ages1{"34", "3"}; // brakect init: fills remain with empty string
std::array<int, 10> ages2 = {3, 4, 3}; // Equals init:  the first 3/10 elements init with equals
std::array<float, 5> ages3 {}; // init all value to 0.0
array<float, 5> scores ={}; // same init all with 0

std::vector<float> age6(5, 3.5f); // fill all 5 init elements with 3.5f
std::vector<int> age7{ 3, 5, 6 }; // bracket init:  with 3 elements 
std::vector<int> age8 = { 13, 15, 26, 5, 11 }; //Equals init: fills with 5 element 
std::vector<int> ageCopy1 (age6); // copy array

ages1[5] = "39";
ages1[9] = "No";
for (auto &i : ages1)
{
 std::cout << i << " ";
}

// Passing an `auto => std::initializer_list<int> li `
auto li = { 4, 0, 200, 45 }; 
std::vector<int> liVec(li.begin(), li.end());
for (auto var : liVec)
	std::cout << var << " ";

std::cout << "\n";

// Passing array as an initializer
float ages[10] = { 3.0f };
std::vector<float> agesf(ages, ages + sizeof(ages)/sizeof(float));

for (auto& i : agesf)
	std::cout << i << " ";

std::cout << "\n";
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

## Classes and Template

When you create a function in a class and put the declaration and definition together, the compiler implicitly create an inline function.

this is the standard way

```c++ title="A.h"
template <class T>
Class A {
  public
  T a_func();

  private:
  T a{};
}

template <class T>
inline T A::a_func(){  return ...; }
```

But you can also put the definition and declaration together

```c++ title="A.h"
template <class T>
Class A {
  public
  // the complier IMPLICITLY call :
  // template <class T> inline T A::a_func()
  T a_func(){  return ...; }

  private:
  T a{};
}


```
