cmake_minimum_required(VERSION 3.0.2)
project(tests_release)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(PATH "../../../../src/test/")
set(SOURCES
    ${PATH}main.cpp
    ${PATH}json_pointer_test.h
    ${PATH}unit_test.h)

find_library (GTEST_LIB gtest)
find_library (JSON_LIB format-json)
find_library (JSON_POINTER_LIB format-json-pointer)

message(${GTEST_LIB})
message(${JSON_LIB})
message(${JSON_POINTER_LIB})

add_executable (tests_release ${SOURCES})
target_link_libraries (tests_release ${GTEST_LIB} ${JSON_LIB} ${JSON_POINTER_LIB})
target_include_directories (tests_release PUBLIC "/usr/local/include")
