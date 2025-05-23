cmake_minimum_required(VERSION 3.10)
project(BankersAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bankers_algorithm
    main.cpp
    banker.cpp
) 