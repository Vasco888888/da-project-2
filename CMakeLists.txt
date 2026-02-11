cmake_minimum_required(VERSION 3.30)
project(DA2025_PRJ2_G24)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(
        DA2025_PRJ2_G24 
        src/main.cpp
        src/loader.cpp
        src/algorithms/bruteforce.cpp
        src/algorithms/greedy.cpp
        src/algorithms/dynamic.cpp
        src/algorithms/hybrid.cpp
)

