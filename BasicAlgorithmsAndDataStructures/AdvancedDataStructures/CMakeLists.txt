cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(AdvancedDataStructures)

set( CMAKE_CXX_STANDARD 11 )

set( SRC_FILES main.cpp btree.cpp)
set( HEADER_FILES btree.h)

#Cuda compilation
set( CMAKE_CXX_FLAGS_DEBUG "-Wall")
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -O3")
add_executable(AdvancedDataStructuresDemo ${SRC_FILES} ${HEADER_FILES})

