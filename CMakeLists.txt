cmake_minimum_required(VERSION 3.24)
project(latticeAnimals)

set(CMAKE_CXX_STANDARD 20)

add_executable(latticeAnimals src/main.cpp src/AnimalCounter.cpp src/Signature.cpp)
