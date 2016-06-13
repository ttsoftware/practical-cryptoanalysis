cmake_minimum_required(VERSION 3.2)
project(exercises_and_projects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
set(SOURCE_FILES src/main.cpp src/lib/Encrypter.h)

add_executable(exercises_and_projects ${SOURCE_FILES})

find_package(OpenSSL)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries (exercises_and_projects ${OPENSSL_LIBRARIES})
endif (OPENSSL_FOUND)

