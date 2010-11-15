# Gruppe 02
# Serie 01
# Matthias Boehm, 895778
# Hannes Georg, 850360

cmake_minimum_required(VERSION 2.4)

PROJECT(MultInf)
SET(LIBRARY_OUTPUT_PATH "${MultInf_BINARY_DIR}/lib")
SET(EXECUTABLE_OUTPUT_PATH "${MultInf_BINARY_DIR}/bin")

INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR})
INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR}/Graphics2DBase)
INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR}/Graphics2D)

OPTION(BUILD_SHARED_LIBS "Build HelloWorld with shared libraries." OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(Graphics2D)
add_subdirectory(Graphics2DBase)

add_executable(testGraphics2D testGraphics2D.cpp)
add_executable(testPrimitives testPrimitives.cpp)
add_executable(testGUI testGUI.cpp)

target_link_libraries(testGraphics2D Graphics2DBase Graphics2D)
target_link_libraries(testPrimitives Graphics2DBase Graphics2D)
target_link_libraries(testGUI Graphics2DBase Graphics2D)
