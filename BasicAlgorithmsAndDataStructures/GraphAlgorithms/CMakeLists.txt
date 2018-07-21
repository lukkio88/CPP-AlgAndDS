cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(GraphAlgorithms)

set( CMAKE_CXX_STANDARD 11 )

include_directories(./)

#set( SRC_FILES graph.cpp)
set( HEADER_FILES graph.h)

#add_library(graph-algorithms SHARED ${HEADER_FILES})