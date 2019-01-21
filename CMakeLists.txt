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

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-reorder -pthread")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
#find_package(Lua REQUIRED)

if(APPLE)
    find_library(BZ2_LIB bz2)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CV_LIBRARY CoreVideo)
    include_directories(/usr/local/include)
endif (APPLE)


include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
#link_directories(${LIB_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# source directory
add_subdirectory(src)



