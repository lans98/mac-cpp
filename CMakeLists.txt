cmake_minimum_required(VERSION 3.10)
project(mac) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src/include)

add_executable(determinant test/determinant.cpp)
add_executable(inverse test/inverse.cpp)

set_target_properties(
    determinant
    inverse
    
    PROPERTIES
    LINK_LIBRARIES armadillo)
