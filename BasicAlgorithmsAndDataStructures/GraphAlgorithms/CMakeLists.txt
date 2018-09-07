cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(GraphAlgorithms)

set( CMAKE_CXX_STANDARD 11 )

include_directories(./)
include_directories(../ElementaryDataStructures)

set( HEADER_FILES graph.h)
set( SRC_FILES graph.cpp)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
endif()

add_library(graph-algorithms SHARED ${SRC_FILES} ${HEADER_FILES})
set_target_properties(graph-algorithms PROPERTIES runtime_output_directory ${CMAKE_BINARY_DIR})