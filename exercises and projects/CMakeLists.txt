cmake_minimum_required(VERSION 3.2)
project(exercises_and_projects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES src/sheet0/main.cpp src/sheet0/Encrypter.h)
add_executable(exercises_and_projects ${SOURCE_FILES})