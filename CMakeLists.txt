cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CC_STANDARD 11)
set(CMAKE_CC_STANDARD_REQUIRED ON)

project(qsa)

cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE src_list "*.h" "*.c")

add_executable(isa-pso ${src_list})

include_directories(${CMAKE_SOURCE_DIR}/src)
