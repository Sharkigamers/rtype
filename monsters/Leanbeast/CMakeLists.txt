cmake_minimum_required(VERSION 3.8)

project (Leanbeast)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
add_library(Leanbeast SHARED Leanbeast.cpp entryPoint.cpp)