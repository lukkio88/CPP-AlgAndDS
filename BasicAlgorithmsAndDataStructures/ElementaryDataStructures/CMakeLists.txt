cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ElementaryDataStructures)

set( CMAKE_CXX_STANDARD 11 )

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
endif()

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE IMPLEMENTATION_FILES "*.tcc")

source_group(Implementation FILES ${IMPLEMENTATION_FILES})
#list(TRANSFORM ${SRC_FILES} PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(elementary-data-structures INTERFACE)
target_include_directories(elementary-data-structures INTERFACE "./")
add_custom_target(ElementaryDataStructures SOURCES ${HEADER_FILES} ${IMPLEMENTATION_FILES})