cmake_minimum_required(VERSION 3.3)

project(bubble VERSION 1.0.1 DESCRIPTION "lib for bubble bobble")

find_package(Lua REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../include ${LUA_INCLUDE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(bubble SHARED
    zenchan.cpp
    factories.cpp
)