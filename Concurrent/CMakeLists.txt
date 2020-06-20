CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Concurrent)

SET(CMAKE_BUILE_TYPE RELEASE)
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall")
SET(CMAKE_CXX_FLAGS "-std=c++0x -O3 -pthread")

SET(SRC_ROOT ${PROJECT_SOURCE_DIR}/src)

add_executable(thread ${SRC_ROOT}/thread.cpp)

add_executable(thread_mutex ${SRC_ROOT}/thread_mutex.cpp)

add_executable(thread_mutex_lock_guard ${SRC_ROOT}/thread_mutex_lock_guard.cpp)

add_executable(thread_mutex_lock_guard_unique_lock ${SRC_ROOT}/thread_mutex_lock_guard_unique_lock.cpp)

