cmake_minimum_required(VERSION 3.25)
project(OOP_Labs)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Опции для выбора лабораторных работ
option(BUILD_LAB1 "Build Lab 1" OFF)
option(BUILD_LAB2 "Build Lab 2" OFF)
option(BUILD_LAB3 "Build Lab 3" OFF)
option(BUILD_LAB4 "Build Lab 4" OFF)
option(BUILD_LAB5 "Build Lab 5" OFF)
option(BUILD_LAB6 "Build Lab 6" OFF)
option(BUILD_LAB7 "Build Lab 7" OFF)


# Добавление подпроектов в зависимости от опций
if(BUILD_LAB1)
    add_subdirectory(Labs/L1-First_CPP_Program)
endif()

if(BUILD_LAB2)
    add_subdirectory(Labs/L2-Classes)
endif()

if(BUILD_LAB3)
    add_subdirectory(Labs/L3-Inheritance)
endif()

if(BUILD_LAB4)
    add_subdirectory(Labs/L4-Basics_of_metaprogramming)
endif()

if(BUILD_LAB5)
    add_subdirectory(Labs/L5-Iterators_and_allocators)
endif()

if(BUILD_LAB6)
    add_subdirectory(Labs/L6-Design_patterns)
endif()

if(BUILD_LAB7)
    add_subdirectory(Labs/L7-Async_programming)
endif()