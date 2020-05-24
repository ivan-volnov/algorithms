cmake_minimum_required(VERSION 3.5)

project(algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

add_executable(algorithms
    algorithms.h
    main.cpp
    sorting_algorithms.h
)
