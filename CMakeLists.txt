cmake_minimum_required(VERSION 3.3)

set(ROOT_VERSION 1)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(VERSION ${ROOT_VERSION}.${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
project(glib VERSION ${VERSION})

# set environment variables and flags
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(BIN_DIR ${PROJECT_DIR}/bin)
set(LIB_DIR ${PROJECT_DIR}/lib)
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(SRC_DIR ${PROJECT_DIR}/src)
set(PYBIND_INCLUDE_DIR ${PROJECT_DIR}/pybind11/include)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")

set(CMAKE_CXX_FLAGS "-pthread -DBT_USE_DOUBLE_PRECISION")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
if (WIN32)
    SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif (WIN32)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc")
ENDIF(MSVC)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
#find_package(Lua REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

if(APPLE)
    find_library(BZ2_LIB bz2)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CV_LIBRARY CoreVideo)
    include_directories(/usr/local/include)
endif (APPLE)


#include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
#link_directories(${LIB_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


configure_file (
    "${INCLUDE_DIR}/version.h.in"
    "${INCLUDE_DIR}/version.h"
)

# source directory
add_subdirectory(pybind11)
add_subdirectory(src/alglib)
add_subdirectory(src/monkey)
add_subdirectory(src/scumm)
add_subdirectory(src/smb)
add_subdirectory(src/prova)

