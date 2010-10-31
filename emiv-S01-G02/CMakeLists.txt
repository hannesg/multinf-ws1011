# Gruppe 02
# Serie 01
# Matthias Boehm, 895778
# Hannes Georg, 850360

cmake_minimum_required(VERSION 2.4)

PROJECT(MultInf)
SET(LIBRARY_OUTPUT_PATH "${MultInf_BINARY_DIR}/lib")
SET(EXECUTABLE_OUTPUT_PATH "${MultInf_BINARY_DIR}/bin")

INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR})

OPTION(BUILD_SHARED_LIBS "Build HelloWorld with shared libraries." OFF)

add_executable(helloworld helloworld.cpp)

# target_link_libraries(HelloWorld ...)
