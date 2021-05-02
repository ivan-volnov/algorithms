cmake_minimum_required(VERSION 3.5)

project(algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

find_package(Catch2 REQUIRED)

add_executable(algorithms
    src/algorithms.hpp
    src/test.cpp
    src/rb_tree.hpp
    src/sorting_algorithms.hpp
    src/static_circular_buffer.hpp
    src/static_stack.hpp
)

target_link_libraries(${PROJECT_NAME}
    Catch2::Catch2
)
