
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

## Namespaces demonstration

Namespaces helps use `Modularize` Code
Namespaces are used to avoid name clashes either within your program or with the built in C++ functions and classes

```c++

#include <iostream>
#include <cstdio>
using std::cout, std::endl, std::cin; // using the C++17

namespace dst1{
 float Distance(int s, int r) { return (s * r) / 2; }
 int max(int a, int b) { return (a > b) ? a : b; }
}

namespace dst2{
 float Distance(int x, int y) { return (x * x + y * y) / 2; }

}

int main() {
 std::string name;
 cout << "Enter your name: ";
 cin >> name;
 cout << "Ahoyy, Your name is "<< name << endl;

 // Calling from 'dst1' namespace
 cout << dst1::Distance(34, 12) << endl;
 cout << dst1::max(45, 500) << endl;

 // Calling from 'dst2' namespace
 cout << dst2::Distance(23, 50) << endl;
 
 return EXIT_SUCCESS;
}

```

Example of namespace Nesting

```c++
#include <iostream>
using std::cout, std::endl;


namespace sort {
 /** Sorting Algoorithms */
 void QuickSort() {cout << "Q-sort" << endl;}

 void InsertSort() {cout << "I-sort" << endl;}

 void BinarySort() {cout << "Bi-sort" << endl;}

 namespace comp {
  /** Comp - stands for `comparison` */
  void LessThan() {cout << "Less than " << endl;}

  void GreaterThan() {cout << "Greater than " << endl;}
 } // nested 
}

int main() {
 
 sort::BinarySort();
 sort::InsertSort();
 sort::comp::LessThan();
 sort::comp::GreaterThan();

 return EXIT_SUCCESS;
}
```

## Using Getline to read lines

`Getline`is part of `string` library

```c++
#include <iostream>
#include <string>

int main() {
 std::string name;
 std::cout << "What is your name: ";

 std::getline(std::cin, name);

 if (name.find(' ') == 0) { // check for space
  std::cout << "Space found \n";
  return EXIT_FAILURE;
 }

 std::cout << "Hello, " << name << std::endl;

 return EXIT_SUCCESS;
}
```

## Using Cmath to work math in C++

```c++

#include <iostream>
#include <iomanip> // for `std::setprecision`
#include <cmath>
using std::cout, std::endl;

int main() {

 cout << " sqrt of 25 = " << std::sqrt(25.0f) << endl;
 cout << " Max of 6, 4 = " << std::max(6, 4) << endl;
 cout << "Min of 45, 78 = " << std::min(45, 78) << endl;
 cout << "floor of 45.95 = " << std::floor(45.95) << endl;
 cout << "ceil of 20.41 = " << std::ceil(20.41) << endl;
 float var1 = 54.34454f;
 cout << " Round "<<var1<<" to two decimal = " 
  << std::fixed << std::setprecision(2) << var1 << endl;


}

```


## Classes Basics

### Example 1

#### Base.h

```c++ title="Base.h"
#pragma once

#include <string>
#include <iostream>

class Car {

private:
 std::string name= std::string("Unknown"); // set default name
 float fuel{ 0.0f }; // {} to initialier
 float speed{ 0.0f };
 int passenger{ 0 };

public:
 Car();
 Car(std::string name, float amount);
 void fillFuel(float amount);
 void accelerate();
 void breake();
 void addPassenger(int passenger);
 void dashboard();
 ~Car();
};
```

#### Base.cpp

```c++ title="Base.cpp"
#include "Base.h"

Car::Car(){
 dashboard();
}

Car::Car(std::string name, float amount){
 this->name = name;
 fuel = amount;

 dashboard();

}

void Car::fillFuel(float amount){
 fuel += amount;
}

void Car::accelerate(){
 speed++;
 fuel -= 0.5f;
}

void Car::breake(){
 speed = 0;
 fuel -= 0.5f;
}

void Car::addPassenger(int passenger){
 this->passenger += passenger;
}

void Car::dashboard(){
 std::cout << "< ===   DASHBOARD === >\n";
 std::cout << "Car name: " << name << "\n";
 std::cout << "Car fuel: " << fuel << "\n";
 std::cout << "Car passenger: " << passenger << "\n\n";
 std::cout << "Speed: " << speed << "\n";
}

Car::~Car(){}

```

#### Main.cpp

```c++ title="Main.cpp"
#include <iostream>
#include <vector>
#include <array>

#include "Base.h"

using std::array;
using std::vector;


int main() {

 Car c1;
 int x = 40; // fuel
 Car c2("Xp90", 30);

 c2.addPassenger(4);
 c2.dashboard();

 c2.fillFuel(x);
 c2.dashboard();

 c2.accelerate();
 c2.accelerate();
 c2.accelerate();
 c2.accelerate();

 c2.dashboard();

 return 0;
}
```

## Basic Dynamic Memory allocation

### Working with Malloc

```c++
#include <stdio.h>
#include <stdlib.h>

int main() {
  int* p = (int*)malloc(sizeof(int)); // allocate memory
  *p = 5;
  *p = *p + 7;
  printf("%d", *p); // print value
  free(p);
}
```

### Working with Calloc

```c++
float* prices = (float*)calloc(5, sizeof(float));

for (size_t i = 0; i < 5; i++)
{
  float val = 56.65;
  prices[i] += val * i;
  printf("%f\n", prices[i]);
}

free(prices);
prices = nullptr;
```

### Allocating memory with 'new' operator

```cpp

/*** 
  Allocating memory through `new` Operator:
  Computer knows exactly what size 'int' so it allocate it automatically
  One can assign default value for new allocator unlike 'malloc' 
  */
int* p0 = new int;
int* p1 = new int{}; // default 0
int* p2 = new int{45}; // default 45
int* p3 = new int(23); // default 23


*p0 = 110;

std::cout << *p0 << "\n";
std::cout << *p1 << "\n";
std::cout << *p2 << "\n";
std::cout << *p3 << "\n";

delete p1, p2, p3, p0;
p1 = p2 = p3 = p0 = nullptr;

// More Examples
void String() 
{
    int LENGTH = 5;
    char* lang = new char[LENGTH];
    strcpy_s(lang, LENGTH, "Pyth"); // Alloc one extra bite
    std::cout << lang << "\n";
}

```

# Constant Member Functions

* Member functions qualified with `const` keyword
* Both declaration and definition is qualified
* Such functions **cannot change value of any member variables**
* Useful for creating read-only functions
* Constant objects can invoke only constant member functions.
  * This means all its members identifiers(variables) are also constant

```c++ titlle="Person.h"
#pragma once
#include <iostream>

class Person
{
  std::string username{};
  bool isHealthy{};
  float eneryStored{};
  static int userCount;

public:
  Person();
  Person(std::string);
  void walk();
  void displayPersonDetails() const;
  static void showUserCount();
};
```

```c++ title="Person.cpp"
#include "Person.h"

int Person::userCount = 0;

Person::Person(){
  userCount++;
}

Person::Person(std::string name) : username(name){
  userCount++;
}

void Person::walk(){
  this->eneryStored += 3.4f;
}

void Person::displayPersonDetails() const{
  std::cout << "This person " << this->username << " has  " << this->eneryStored << " Energy.\n";
}

void Person::showUserCount() {
  std::cout << "Total users = " << userCount << "\n";
}
```

```c++ title="Main.cpp"
#include "Person.h"


int main() {

  Person p1, p2, p3;
  const Person p4("Pastor Iwo");
  //p4.walk();
  //p4.walk();
  //p4.walk();
  p4.displayPersonDetails(); // read-only 
  Person::showUserCount();
  return 0;
}

```
