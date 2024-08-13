cmake_minimum_required(VERSION 2.8.3)

find_package(OpenCV REQUIRED)
if (OpenCV_VERSION)
  message(STATUS "OpenCV version: " ${OpenCV_VERSION})

  if(${OpenCV_VERSION_MAJOR} LESS 2 OR (${OpenCV_VERSION_MAJOR} EQUAL 2 AND ${OpenCV_VERSION_MINOR} LESS 3))
    message(FATAL_ERROR "You need OpenCV version 2.3.0 or later!")
  endif()
endif()

include_directories(include)
file(GLOB_RECURSE sources src/*.cpp)
add_library(lib STATIC ${sources})
target_link_libraries(lib ${OpenCV_LIBS})
add_executable(run src/main.cpp)
target_link_libraries(run lib)
