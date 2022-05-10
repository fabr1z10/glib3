cmake_minimum_required(VERSION 3.3)

#set(ROOT_VERSION 1)
#set(MAJOR_VERSION 0)
#set(MINOR_VERSION 0)
#set(PATCH_VERSION 0)
#set(VERSION ${ROOT_VERSION}.${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
#
## uncomment this to use assimp
##set(USE_ASSIMP ON)
##set(USE_BOX2D ON)
set(USE_BULLET ON)
#
#project(glib VERSION ${VERSION})
#
#set(_pf_x86 "Program\ Files\ \(x86\)")
#
## set environment variables and flags
#cmake_policy(SET CMP0074 NEW)
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(SRC_DIR ${PROJECT_DIR}/src)
set(PYBIND_INCLUDE_DIR ${PROJECT_DIR}/include/py/include)
#
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
#

set(CMAKE_CXX_FLAGS "-pthread")
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
#if (WIN32)
#    SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#endif (WIN32)
#
#IF(MSVC)
#    SET(CMAKE_CXX_FLAGS "/EHsc")
#	set(glm_DIR c:/users/fabve/Downloads/glm/cmake/glm)
#	set(ENV{FREETYPE_DIR} $ENV{ProgramFiles\(x86\)}\\freetype)
#	set(ENV{PNG_ROOT} $ENV{ProgramFiles\(x86\)}\\libpng)
#	set(JPEG_INCLUDE_DIR c:/Users/fabve/Downloads/jpeg-9d)
#	set(JPEG_LIBRARY_RELEASE c:\\Users\\fabve\\Downloads\\jpeg-9d\\Release\\x64)
#ENDIF(MSVC)
#
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(yaml-cpp REQUIRED)

#if(DEFINED USE_ASSIMP)
#    find_package(ASSIMP REQUIRED)
#endif(DEFINED USE_ASSIMP)
#
##if (DEFINED USE_BOX2D)
#find_package(box2d REQUIRED)
##endif (DEFINED USE_BOX2D)
#
if (DEFINED USE_BULLET)
  find_package(Bullet REQUIRED)
endif (DEFINED USE_BULLET)
#
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
#
#if(APPLE)
#    find_library(BZ2_LIB bz2)
#    find_library(COCOA_LIBRARY Cocoa)
#    find_library(IOKIT_LIBRARY IOKit)
#    find_library(CV_LIBRARY CoreVideo)
#    include_directories(/usr/local/include)
#endif (APPLE)
#
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#
#configure_file (
#    "${INCLUDE_DIR}/version.h.in"
#    "${INCLUDE_DIR}/version.h"
#)
#
## source directory
add_subdirectory(include/py)
add_subdirectory(src/alglib)
add_subdirectory(src/monkey)
##add_subdirectory(src/scumm)
##add_subdirectory(src/racer)
##add_subdirectory(src/smb)
##add_subdirectory(src/platformer)
#add_subdirectory(src/prova)
##add_subdirectory(src/mogo)

