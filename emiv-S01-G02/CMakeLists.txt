cmake_minimum_required(VERSION 2.4)

PROJECT(HelloWorld)
SET(LIBRARY_OUTPUT_PATH "${HelloWorld_BINARY_DIR}/lib")
SET(EXECUTABLE_OUTPUT_PATH "${HelloWorld_BINARY_DIR}/bin")

INCLUDE_DIRECTORIES(${HelloWorld_SOURCE_DIR})

OPTION(BUILD_SHARED_LIBS "Build HelloWorld with shared libraries." OFF)

add_executable(HelloWorld HelloWorld.cpp)

# target_link_libraries(HelloWorld ...)
