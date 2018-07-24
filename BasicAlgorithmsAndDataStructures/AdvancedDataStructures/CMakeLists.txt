cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(AdvancedDataStructures)

set( CMAKE_CXX_STANDARD 11 )

include_directories(./)

set( SRC_FILES vEB.cpp btree.cpp fibonacciHeap.cpp)
set( HEADER_FILES vEB.h btree.h fibonacciHeap.h)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
endif()

add_library(advanced-data-structures SHARED ${SRC_FILES} ${HEADER_FILES})
set_target_properties(advanced-data-structures PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})