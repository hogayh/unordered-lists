cmake_minimum_required(VERSION 3.16)
project(unordered_lists LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Drivers
add_executable(ArrayListDriver
        ArrayListDriver.cpp
        # Customer.cpp   # uncomment if needed
)

add_executable(LinkedListDriver
        LinkedListDriver.cpp
        # Customer.cpp
)

# ---- Optional tests (only if files actually exist) ----
option(BUILD_TESTS "Build test executables" OFF)

if(BUILD_TESTS)
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests/catch_main_array.cpp")
        add_executable(ArrayTest
                tests/catch_main_array.cpp
                # add your array list sources here as needed
        )
    endif()

    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests/catch_main_linked.cpp")
        add_executable(LinkedTest
                tests/catch_main_linked.cpp
                # add your linked list sources here as needed
        )
    endif()
endif()
