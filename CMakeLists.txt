cmake_minimum_required(VERSION 3.30)
project(DA2025_PRJ2_G24)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        DA2025_PRJ2_G24 main.cpp
        loader.cpp
        algorithms/bruteforce.cpp
        algorithms/greedy.cpp
        algorithms/dynamic.cpp
        algorithms/hybrid.cpp
)
