# JSON Pointer
[JSON Pointer](https://tools.ietf.org/html/rfc6901) defines a string syntax for identifying a specific value
within a JavaScript Object Notation (JSON) document.
## Requirements
- C++ compiler supporting the C++11 standard, such as GCC >= 4.5 or Clang >= 3.3
- [JSON for C++](https://github.com/karekoho/json-pointer)
## Installation
### 1.Install JSON for C++:
```
git clone https://github.com/karekoho/json.git
```
In the _root of the repository_ run the following commands:
```
cmake . 
make & make install
```
A shared library called `libjson` will be created in `/usr/local/lib`.
The development headers will be found in `/usr/local/include/format`.
### 2. Install JSON Pointer:
```
git clone https://github.com/karekoho/json-pointer.git
```
In the _root of the repository_ run the following commands:
```
cmake . 
make & make install
```
A shared library called `libjson_pointer` will be created in `/usr/local/lib`
The development headers will be found in `/usr/local/include/format`
### 3. Include 
```c++
#include <format/json.h>
#include <format/json_pointer.h>
```
in your source code to use JSON Pointer.
# Usage
```c++
#include <format/json.h>
#include <format/json_pointer.h>
#include <iostream>
#include <array>

using namespace format;

// Create a JSON pointer object
json::json_pointer jp (L"/foo/1");

// Create a JSON object
json::json j = L"{ \"foo\": [\"bar\", \"baz\"],\
              \"\": 0,\
              \"a/b\": 1,\
              \"c%d\": 2,\
              \"e^f\": 3,\
              \"g|h\": 4,\
              \"i\\j\": 5,\
              \" \": 7,\
              \"m~n\": 8 }";

// Get the value the pointer refers to
json::value & v = jp.value (j);

std::wcout << v.as<const wchar_t *>() << std::endl;
// ouput: baz

// Create an array of JSON pointers
std::array<format::json::json_pointer, 13> jp_list = {
    // pointer:      // output:
    L"",            // the whole document
    L"/foo",        // ["bar", "baz"]
    L"/foo/0",      // "bar"
    L"/",           // 0
    L"/a~1b",       // 1
    L"/c%d",        // 2
    L"/e^f",        // 3
    L"/g|h",        // 4
    L"/i\\j",       // 5
    L"/ ",          // 7
    L"/m~0n",       // 8
    L"/notfound",   // empty string
    L"/not/found"   // exception
};

for (auto& jp : jp_list)
  {
    try {
      // Get the value the pointer refers to
      json::value & v =  jp.value (j);

      // If value is not found, object type is undefined
      if (v.type () == json::value::undefined_t)
        std::wcout << "Value not found" << std::endl;
      else
        std::wcout << v.stringify () << std::endl;

    } catch (json::json_pointer_error & e) {
      // Invalid pointer syntax or
      // a pointer that references a nonexistent value
      std::wcerr << e.what () << std::endl;
    }
  }

//  output:
//  {"i\j":5," ":7,"g|h":4,"a/b":1,"":0,"e^f":3,"c%d":2,"m~n":8,"foo":["bar","baz"]}
//  ["bar","baz"]
//  "bar"
//  0
//  1
//  2
//  3
//  4
//  5
//  7
//  8
//  Value not found
//  Key pointing elsewhere than the end of the path must exist. Non-existent key is preceding 'found'
```
