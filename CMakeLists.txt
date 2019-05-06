cmake_minimum_required(VERSION 3.10)
project(mac) 

find_package(SFML 2.5 COMPONENTS window REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src/include)

add_executable(determinant test/determinant.cpp)
add_executable(inverse test/inverse.cpp)
add_executable(vec_space test/vector_space.cpp)
add_executable(linear_trans test/linear_transformation.cpp)
add_executable(rotate_poly test/rotate_polygon.cpp)

set_target_properties(
    determinant
    inverse
    vec_space 
    linear_trans
    rotate_poly
    
    PROPERTIES
    LINK_LIBRARIES armadillo
)

set_property(
    TARGET rotate_poly
    APPEND PROPERTY 
    LINK_LIBRARIES sfml-window sfml-graphics
)
