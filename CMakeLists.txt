cmake_minimum_required(VERSION 2.6)
project(ShortestPath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCES_MAIN
	main.cpp)
set(HEADERS_MAIN
	delaunay.h
	edge.h
	vector2.h
	triangle.h
	steiner.h
	prim.h)

set(SOURCES_TEST
	testmain.cpp)
set(HEADERS_TEST
	delaunay.h
	edge.h
	vector2.h
	triangle.h
	steiner.h
	prim.h)
	
include_directories("files")

add_executable(main ${SOURCES_MAIN} ${HEADERS_MAIN})
add_executable(test ${SOURCES_TEST} ${HEADERS_TEST})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/files/ 
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} 
	PATTERN .c)
