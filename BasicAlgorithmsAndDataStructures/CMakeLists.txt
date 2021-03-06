cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CPP_Algorithms_and_Data_Structures)

set( CMAKE_CXX_STANDARD 11 )

add_subdirectory(./ElementaryAlgorithms)
add_subdirectory(./ElementaryDataStructures)
add_subdirectory(./AdvancedDataStructures)
add_subdirectory(./GraphAlgorithms)
add_subdirectory(./Testing)

set(INCLUDE_FOLDERS 
	./ElementaryAlgorithms 
	./ElementaryDataStructures 
	./AdvancedDataStructures 
	./GraphAlgorithms
	./Testing)

include_directories(${INCLUDE_FOLDERS})

set(SRC_FILES main.cpp)

add_executable(alg-and-ds ${SRC_FILES})
target_link_libraries(alg-and-ds 
	elementary-algorithms
	elementary-data-structures
	advanced-data-structures
	test)