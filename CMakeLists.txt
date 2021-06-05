cmake_minimum_required(VERSION 3.0.2)
project(format-json-pointer)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCES
    src/json_pointer/json_pointer.cpp
# headers
    src/json_pointer/json_pointer.h
    src/json_pointer/json_pointer_global.h
    src/json_pointer/json_pointer_exception.h)

# Create libjson_pointer
add_library(format-json-pointer SHARED ${SOURCES})

# Link to libjson
find_library(JSON_LIB format-json)
target_link_libraries (format-json-pointer PUBLIC "${JSON_LIB}")

# TODO: find_path (JSON_PATH "json.h")
# TODO: target_include_directories (json_pointer PUBLIC "${JSON_PATH}")
target_include_directories (format-json-pointer PUBLIC "/usr/local/include")

install(TARGETS format-json-pointer DESTINATION lib)
install(DIRECTORY src/json_pointer/ DESTINATION include/format FILES_MATCHING PATTERN "*.h")

# If “make install” is invoked or INSTALL is built, this directory is prepended onto all install directories.
# This variable defaults to /usr/local on UNIX and c:/Program Files on Windows
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install

