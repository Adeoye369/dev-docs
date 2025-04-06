
# Templating in CPP

## Introduction to Templating
Example of templating:

```cpp
#include <iostream>

using std::cout, std::cin;

template<typename I>
I Max(I x, I y) {

    return ( x > y) ? x : y;
}

template<>
std::string Max (std::string x, std::string y) {
    return (x.length() > y.length()) ? x : y;
}

int main(int argv, char argc) {
    int x = 4;
    int y = 7;
    cout << " Max of num " << x <<", " << y << " = " << Max<int>(x, y) << "\n";

    float x1 = 4.5;
    float y1 = 8.1;
    cout << " Max of float " << x1 <<", " << y1 << " = " << Max<float>(x1, y1) << "\n";


    std::string x2 = "usomestring1";
    std::string x3 = "tstring2 is the long string here";
    cout << "Max of string = " << Max<std::string>(x2, x3) << "\n";

    return EXIT_SUCCESS;
}
```

## Explicit Specialization 

```cpp

template<typename I>
I Max(I x, I y) {
    return ( x > y) ? x : y;
}

// Explicit Specializatioon
template<>
const char* Max (const char* x, const char* y) {
    return (strcmp(x, y) > 0) ? x : y;
}

int main(int argv, char argc) {


    const char* s = "'AAAB'";  // Max is here because of B in string
    const char* a = "'AAAA'";
    cout << Max(s, a) << "\n";

}
```

## Non-type Template Arguments

### Basic 
Non-type template works usually with arrays and classes.
the `arrSize` in the template is the **non-type argument**.
It must always be constant. We will find an example in the standard cpp template array
`std::array<float, 10> arr3`

```cpp

template<typename T, int arrSize>
T Max(T* pArr) {

    T curr_max = 0;
    for (int i = 0; i < arrSize; i++)
        if (pArr[i] > curr_max) 
            curr_max = pArr[i];

        return curr_max;
}

template<typename T, int size>
T Sum(T* pArr) {
    T sum{};
    for (int i = 0; i < size; i++)
        sum += pArr[i];

    return sum;
}

int main(int argv, char argc) {


    int arr1[]{ 4, 3, 5, 4, 11, -2 };
    cout << Sum<int, 6>(arr1) << "\n";
    cout << Max<int, 6>(arr1) << "\n";

	return EXIT_SUCCESS;
}
```

### Using Ref to an array

With this you don't need to specify the size 

```cpp
template<typename T, int size>
T Sum(T(&rArr)[size]) {
    T sum{};
    for (int i = 0; i < size; i++)
        sum += rArr[i];

    return sum;
}

int main(int argv, char argc) {

    int arr1[] = { 4, 3, 5, 4, 11, -2 };
    int(&rArr)[6] = arr1; // reference to an array
    int* arr2 = arr1;

    cout << Sum(arr1) << "\n"; // No need to specify size

    double arrD[] = { 34.5, 112,45.7, 45.11111, 90.409 };
    cout << Sum<double>(arrD) << "\n";

}
```
