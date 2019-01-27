cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Testing)
set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_FOLDERS ./ ../ElementaryDataStructures)
set(HEADER_FILES list_testing.h bst_testing.h rb_tree_testing.h)
set(SRC_FILES list_testing.cpp bst_testing.cpp rb_tree_testing.cpp)
include_directories(${INCLUDE_FOLDERS})

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
endif()

add_library(test ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(test elementary-data-structures)