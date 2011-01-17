# Gruppe 02
# Serie 01
# Matthias Boehm, 895778
# Hannes Georg, 850360

cmake_minimum_required(VERSION 2.4)

cmake_policy(SET CMP0003 NEW)

PROJECT(MultInf)

SET(MultInf "0.1")

SET(LIBRARY_OUTPUT_PATH "${MultInf_BINARY_DIR}/lib" CACHE PATH "This is where the libraries go.")
SET(EXECUTABLE_OUTPUT_PATH "${MultInf_BINARY_DIR}/bin" CACHE PATH "This is where the binaries go.")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MultInf_BINARY_DIR}/bin" CACHE PATH "This is where runtime DLLs go.")

INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR})
INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR}/Graphics2DBase)
INCLUDE_DIRECTORIES(${MultInf_SOURCE_DIR}/Graphics2D)

SET(CMAKE_MODULE_PATH ${MultInf_SOURCE_DIR})

OPTION(BUILD_SHARED_LIBS "Build HelloWorld with shared libraries." ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

OPTION(USE_GTK "Use GTK+ instead of GLUT" OFF)

IF(USE_GTK)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGRAPHICS2D_USEGTK")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EMultInf_SOURCE_DIR})
ENDIF(USE_GTK)

add_subdirectory(Graphics2D)
add_subdirectory(Graphics2DBase)

add_executable(testGraphics2D testGraphics2D.cpp)
add_executable(testPrimitives testPrimitives.cpp)
add_executable(showImage showImage.cpp)
add_executable(testGUI testGUI.cpp)
add_executable(testScanline testScanline.cpp)
add_executable(testConversion testConversion.cpp)
add_executable(testFilter testFilter.cpp)
add_executable(testFilter2 testFilter2.cpp)
add_executable(testSegmentation testSegmentation.cpp)
add_executable(testFeatures testFeatures.cpp)
add_executable(testStructureTensor testStructureTensor.cpp)

target_link_libraries(testGraphics2D Graphics2DBase Graphics2D)
target_link_libraries(testPrimitives Graphics2DBase Graphics2D)
target_link_libraries(showImage Graphics2D)
target_link_libraries(testGUI Graphics2DBase Graphics2D)
target_link_libraries(testScanline Graphics2DBase Graphics2D)
target_link_libraries(testConversion Graphics2DBase Graphics2D)
target_link_libraries(testFilter Graphics2DBase Graphics2D)
target_link_libraries(testFilter2 Graphics2DBase Graphics2D)
target_link_libraries(testSegmentation Graphics2DBase Graphics2D)
target_link_libraries(testFeatures Graphics2DBase Graphics2D)
target_link_libraries(testStructureTensor Graphics2DBase Graphics2D)


