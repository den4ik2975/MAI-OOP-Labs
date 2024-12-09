cmake_minimum_required(VERSION 3.10)
project(L7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add compilation options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Add source files
set(SOURCES
        src/game.cpp
        src/main.cpp
)

# Add header files
include_directories(src/include)

# Create a library with all the source files except main.cpp
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

# Create the executable file
add_executable(${PROJECT_NAME}_exe src/main.cpp)

# Link the library to the executable
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

enable_testing()

add_executable(${PROJECT_NAME}_tests tests/tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME}_lib gtest_main)

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)

# Set output directories
set_target_properties(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)