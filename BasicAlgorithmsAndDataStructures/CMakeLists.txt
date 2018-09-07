cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(CPP_Algorithms_and_Data_Structures)

set( CMAKE_CXX_STANDARD 11 )

#add_subdirectory(./ElementaryAlgorithms)
add_subdirectory(./ElementaryDataStructures)
#add_subdirectory(./AdvancedDataStructures)
#add_subdirectory(./GraphAlgorithms)

#set(INCLUDE_FOLDERS 
#	./
#	./ElementaryAlgorithms 
#	./ElementaryDataStructures 
#	./AdvancedDataStructures 
#	./GraphAlgorithms)

set(INCLUDE_FOLDERS ./ ./ElementaryDataStructures)

set(HEADER_FILES alg-and-ds.h)
set(SRC_FILES main.cpp alg-and-ds.cpp)

add_executable(alg-and-ds ${SRC_FILES} ${HEADER_FILES})
target_include_directories(alg-and-ds PUBLIC ${INCLUDE_FOLDERS})
target_link_libraries(alg-and-ds elementary-data-structures)

#target_link_libraries(alg-and-ds
#	graph-algorithms
#	elementary-data-structures
#	elementary-algorithms
#	advanced-data-structures)