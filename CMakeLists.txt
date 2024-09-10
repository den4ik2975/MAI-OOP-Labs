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


# Опции для выбора лабораторных работ
option(BUILD_LAB1 "Build Lab 1" ON)


# Добавление подпроектов в зависимости от опций
if(BUILD_LAB1)
    add_subdirectory(Labs/L1-First_CPP_Program)
endif()


