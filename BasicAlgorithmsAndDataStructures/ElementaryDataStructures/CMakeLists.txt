cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ElementaryDataStructures)

set( CMAKE_CXX_STANDARD 11 )

include_directories(./)

set( HEADER_FILES list.h allocator.h)
set( SRC_FILES main.cpp list.cpp allocator.cpp)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
endif()

add_library(elementary-data-structures SHARED ${SRC_FILES} ${HEADER_FILES})
add_executable(elementary-data-structure ${SRC_FILES} ${HEADER_FILES})
set_target_properties(elementary-data-structures PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set_target_properties(elemetary-data-structures PROPERTIES LINKER_LANGUAGE CXX)