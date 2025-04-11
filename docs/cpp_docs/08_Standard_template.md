
# Standard Template Library in C++

## Introduction

<div class='grid' markdown>

| Sequence  | Header |
|---------------|------------|
|`array`        | `<array>`|
| `vector`      |`<vector>`|
|`list`         |`<list>`|
|`deque`        |`<deque>`|
|`forward_list`|`<forward_list>`|
|`set, multiset`|`<set>`|
|`map, multimap`|`<map>`|
|`unordered_set, unordered_multiset`|`<unordered_set>`|
|`unordered_map, unordered_multimap`|`<unordered_map>`|


```h
    \** == COMMON FUNCTIONS == **\
    - default constructor
    - uniform Init. construction
    -  Copy constructor
    - Iterator constructor
    - size()
    - clear()
    - begin() and end() 
    - default allocator
```

</div>

## Standard Array Template `std::array`

<div class='grid' markdown>

Properties:     
  1. Thin Wrapper over C-style static array    
  2. Supports iterators     
  3. Knows about its **size**       
  4. provides random access     
  5. Can be used with C-FUNCTIONS       
  6. Cannot grow in size

<figure markdown='span'>
    ![fix size of std::array](img/image-29.png)
</figure>

</div>

```cpp
#include <iostream>
#include <array>


void StdArray() {

    // Initializing using STARDARD INITILIZER LIST
    std::array<uint32_t, 6> scores = {35, 89, 15, 99, 56, 47};

    // Initializing using UNIFORM INITIALIZATION 
    std::array<int, 8> usersNo {1, 4, 8, 16, 20, 32, 46, 64}; 

    // accessing with [] operator
    std::cout << scores[5] << std::endl;

    // accessing element : for range loop
    for (auto& el : scores)
        std::cout << el << " ";
    std::cout << "\n";

    // Accessing element : for loop
    for (int i = 0; i < usersNo.size(); i++){
        std::cout << usersNo[i];
        if (i != (usersNo.size() - 1)) std::cout << " => ";
    }

}

int main() {

    StdArray();
}
```

### Standarrd Array Iterator

- This returns a pointer like object to the current `array`
- User can use this to access the elements by their position
- Iterator also provide overloaded operators such as `++`, `--` and `*`
- You can create it through `begin()` and `end()` functions in all containers

<figure markdown='span'>
    ![std::array structure](img/image-30.png)
</figure>

!!! Warning
    Note that `end()` returns an Iterator that **DOES NOT** point to the array (points to **memory beyond the array** )    Therefore, never dereference an `end()` iterator.





```cpp
void StdArrayIter() {

    std::array<int, 8> usersNo = { 10, 4, 8, 16, 20, 32, 46, 64 };

    // Returns pointer to the begin of the std::array
    auto it = usersNo.begin();
    std::cout << " Access element - *it " << *it << std::endl;
    it++; // move to `4`
    ++it; // move to '8'
    std::cout << " Access element - *it " << *it << std::endl;
    it++;
    --it; // go back to `8`
    it--; // go back  to `4`
    std::cout << " Access element - *it " << *it << std::endl;

    std::cout << "\nPrinting with while loop: \n";
    while (it != usersNo.end()){
        std::cout << *it << " ";
        it++;

    std::cout << "\n\n\n\n" ;

    it = usersNo.begin();
    std::cout << &it << std::endl;
    std::cout << usersNo.data()<< std::endl;


}
```
<div class='grid' markdown>
<figure markdown='span'>
    ![Output from Array demo](img/image-31.png)
</figure>

<figure markdown='span'>
    ![output with data & deref](img/image-32.png)
</figure>

</div>
