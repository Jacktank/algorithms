CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Min_span_tree)

SET(CMAKE_BUILE_TYPE RELEASE) 
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall")
SET(CMAKE_CXX_FLAGS "-std=c++0x")

SET(SRC_ROOT ${PROJECT_SOURCE_DIR}/src)

add_executable(kruskal_1 ${SRC_ROOT}/kruskal_1.cpp)

add_executable(kruskal_2 ${SRC_ROOT}/kruskal_2.cpp)

add_executable(prim ${SRC_ROOT}/prim.cpp)