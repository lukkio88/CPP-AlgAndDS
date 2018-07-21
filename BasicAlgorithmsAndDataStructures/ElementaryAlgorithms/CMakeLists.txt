cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ElementaryAlgorithms)

set( CMAKE_CXX_STANDARD 11 )

include_directories(./)

set( SRC_FILES commons.cpp heapsort.cpp quicksort.cpp)
set( HEADER_FILES commons.h heapsort.h quicksort.h)

add_library(elementary-algorithms SHARED ${SRC_FILES} ${HEADER_FILES})
set_target_properties(elementary-algorithms PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})