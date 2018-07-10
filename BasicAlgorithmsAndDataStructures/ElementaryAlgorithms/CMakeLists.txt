cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ElementaryAlgorithms)

set( CMAKE_CXX_STANDARD 11 )

set( SRC_FILES main.cpp commons.cpp heapsort.cpp quicksort.cpp)
set( HEADER_FILES commons.h heapsort.h quicksort.h)

#Cuda compilation
set( CMAKE_CXX_FLAGS_DEBUG "-Wall")
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -O3")
add_executable(ElementaryAlgorithmsDemo ${SRC_FILES} ${HEADER_FILES})

