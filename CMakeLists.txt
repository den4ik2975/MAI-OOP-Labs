cmake_minimum_required(VERSION 3.25)
project(OOP_Labs)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Опции для выбора лабораторных работ
option(BUILD_LAB1 "Build Lab 1" OFF)
option(BUILD_LAB2 "Build Lab 2" OFF)


# Добавление подпроектов в зависимости от опций
if(BUILD_LAB1)
    add_subdirectory(Labs/L1-First_CPP_Program)
endif()

if(BUILD_LAB2)
    add_subdirectory(Labs/L2-Classes)
endif()
