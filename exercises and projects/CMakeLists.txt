cmake_minimum_required(VERSION 3.5)
project(exercises_and_projects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/exercise0/main.cpp src/exercise0/encrypt.cpp src/exercise0/encrypt.h)
add_executable(exercises_and_projects ${SOURCE_FILES})