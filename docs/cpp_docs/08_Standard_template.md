
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

### Standard Array Iterator

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


## Standard Vector Template `std::vector`


- Behaves like a dynamic array
- Grows automatically
- Efficient for addition/removal at the end
- Provides random access
- Not good for insertion/deletion

`std::vector` is basically a Queue - Expands from one end

<figure markdown='span'>
    ![std vector image](img/image-33.png)
</figure>

```cpp
#include <vector>
template <typename ... Param>
void print(Param... lst) {
    ((std::cout << lst << " "), ...);
        std::cout << std::endl;
}

void StdVector() {
    std::vector<int> xPos = {22, 33, 44, 55};
    xPos.push_back(66);
    xPos.push_back(77);
    xPos.push_back(77);

    std::cout << "\nIteration with for loop:\n";
    for (int i = 0; i < xPos.size(); i++) std::cout << xPos[i] << " ";



    std::cout << "\nIteration with for-range loop:\n";
    for (auto& i : xPos) std::cout << i << " ";

    std::cout << "\nIteration with `begin()`:\n";
    auto it = xPos.begin();
    while (it != xPos.end()) std::cout << *it++ << " ";
        

    xPos.pop_back();
    xPos.pop_back();

    std::cout << "\n";
    for (auto& i : xPos) std::cout << i << " ";

    xPos.insert(xPos.begin(), { 34, 8, 23 }); // insert using init-list
    xPos.insert(xPos.begin(), -101); // insert single element
    xPos.insert(xPos.begin()+3, -33); // insert at index 3

    std::cout << "\n";
    for (auto& i : xPos) std::cout << i << " ";

    xPos.erase(xPos.begin() + (xPos.size() - 1) / 2);

    std::cout << "\n";
    for (auto& i : xPos) std::cout << i << " ";

    xPos.erase(xPos.end() - 3);

    std::cout << "\n";
    for (auto& i : xPos) std::cout << i << " ";

    print(3, 4, 3, 78, "344in", 56.78);
}


int main() {

    StdVector();
}
```

## Standard Deque `std::deque`

- Efficient for additional / Removal at both end
- Grows automatically just like vector
- Provides random access (`[]`operator modify element)
- NOT GOOD for insertion / deletion, except at both ends.
  
Basically what `std::vector` can do but with the extra of front operations

```cpp
  #include <iostream>
#include <deque>

void StdDeque() {

    std::deque<int> songsFreq = {21, 31, 41, 55};
    songsFreq.push_back(66);
    songsFreq.push_back(77);

    songsFreq.push_front(77);
    songsFreq.push_front(12);

    std::cout << "\nIteration with for loop:\n";
    for (int i = 0; i < songsFreq.size(); i++) std::cout << songsFreq[i] << " ";



    std::cout << "\nIteration with for-range loop:\n";
    // Iterating using for-range
    for (auto& i : songsFreq) std::cout << i << " ";

    // Iterating using `begin()`
    std::cout << "\nIteration with `begin()`:\n";
    auto it = songsFreq.begin();
    while (it != songsFreq.end()) std::cout << *it++ << " ";
        

    std::cout << "\nvalue `at` index 5 :  =" << songsFreq.at(5) << std::endl;

    songsFreq.pop_back();
    songsFreq.pop_front();


    std::cout << "\n";
    for (auto& i : songsFreq) std::cout << i << " ";

    songsFreq.insert(songsFreq.begin(), { 34, 8, 23 }); // insert using init-list
    songsFreq.insert(songsFreq.begin(), -101); // insert single element
    songsFreq.insert(songsFreq.begin()+3, -33); // insert at index 3

    std::cout << "\n";
    for (auto& i : songsFreq) std::cout << i << " ";

    songsFreq.erase(songsFreq.begin() + (songsFreq.size() - 1) / 2);

    std::cout << "\n";
    for (auto& i : songsFreq) std::cout << i << " ";

    songsFreq.erase(songsFreq.end() - 3);

    std::cout << "\n";
    for (auto& i : songsFreq) std::cout << i << " ";
}

int main() {

    StdDeque();
}
```



## Standard List `std::list` / Forward list `std::forward_list`

### List

- Implemented as two way linked list
- Efficient for insertion / deletion
-**DOES NOT provide random accesss (NO `[]`operator modify element)**

Useful when you need a container that you will often insert and delete from FRONT/back

```cpp
void List() {
    std::list<float> lf;

    // Populating value using loop
    for (int i = 1; i < 8; i++) 
        lf.push_back(i * 11);

    // Reading value using for-range
    for (auto i : lf) cout << i << " ";
    cout << endl;

    lf.push_front(-11.0);
    lf.push_front(-22.0);
    for (auto i : lf) cout << i << " ";
    cout << endl;

    cout << "insert(..) ONLY at begin() and end() \n";
    lf.insert(lf.begin(), 121);
    lf.insert(lf.end(), 212);
    for (auto i : lf) cout << i << " ";
    cout << endl;

    cout << "erase(..) \n";
    lf.erase(lf.begin());
    lf.pop_front();
    for (auto i : lf) cout << i << " ";
    cout << endl;

    lf.pop_back();
    for (auto i : lf) cout << i << " ";
    cout << endl;

    cout << "clear(..) \n";
    lf.clear();

    cout << "after clearing : ";
    for (auto i : lf) cout << i << " ";
    cout << endl;
}

int main() {
    List();
}
```
<figure markdown='span'>
    ![standard list output](img/image-34.png)
</figure>


### Forward list

- Implemented as one way linked list
- Good for small memory foot print
- Efficient for insertion / deletion
- Does not provide support for size
- Elements are added at the front only
  

```cpp
#include <forward_list>

void ForwardList() {
    std::forward_list<float> fl;

    fl.assign({ 34, 40.0f });

    // Populating value using loop
    for (int i = 1; i < 8; i++)
        fl.push_front(i * 11);

    // Reading value using for-range
    for (auto i : fl) cout << i << " ";
    cout << endl;

    fl.push_front(-11.0);
    fl.push_front(-22.0);
    for (auto i : fl) cout << i << " ";
    cout << endl;

    fl.pop_front();
    for (auto i : fl) cout << i << " ";
    cout << endl;

    cout << "clear(..) \n";
    fl.clear();

    cout << "after clearing : ";
    for (auto i : fl) cout << i << " ";
    cout << endl;

    fl = { 33, 66, 99, 144,169 };
    for (auto i : fl) cout << i << " ";
    cout << "\n\n";

    cout << "insert AFTER begin() : \n";
    fl.insert_after(fl.begin(), 101);
    for (auto i : fl) cout << i << " "; cout << "\n\n";

    cout << "insert AFTER before_begin() : \n";
    fl.insert_after(fl.before_begin(), 202);
    for (auto i : fl) cout << i << " "; cout << "\n\n";

    cout << "erase AFTER begin() : \n";
    fl.erase_after(fl.begin());
    for (auto i : fl) cout << i << " "; cout << "\n\n";

    cout << "erase AFTER before_begin() : \n";
    fl.erase_after(fl.before_begin());
    for (auto i : fl) cout << i << " "; cout << endl;
}

int main() {
    ForwardList();
}
```
<figure markdown='span'>
    ![forward list image](img/image-35.png)
</figure>


## standard Set `std::set` / Multiset `std::multiset`

- Implemented as a binary tree
- Elements are stored and sorted by (< or >)
- Values act as keys
- Fast for search
- No random access
- Elements cannot be modified