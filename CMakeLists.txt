cmake_minimum_required(VERSION 3.16)
project(UnorderedLists LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ArrayTest target
add_executable(ArrayTest
        ArrayADTList.cpp
        Customer.cpp
        Date.cpp
        libs/catch_amalgamated.cpp
        tests/array_test.cpp
)

# LinkedTest target
add_executable(LinkedTest
        LinkedADTList.cpp
        Customer.cpp
        Date.cpp
        libs/catch_amalgamated.cpp
        tests/linked_test.cpp
)

target_include_directories(ArrayTest PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(LinkedTest PRIVATE ${CMAKE_CURRENT_LIST_DIR})
