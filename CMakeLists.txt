cmake_minimum_required(VERSION 3.10)
project(mac) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)
include_directories(src/include)

add_executable(determinante src/determinante.cpp)

set_target_properties(
    determinante 
    
    PROPERTIES
    LINK_LIBRARIES armadillo)
