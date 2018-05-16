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

set(GENERAL_FLAGS "-std=c++11 -Wall -Wno-reorder -MMD -MP -DIL_STD") 
set(CMAKE_CXX_FLAGS_DEBUG "${GENERAL_FLAGS} -g -O0 -D_DEBUG -Wl,--no-as-needed")
set(CMAKE_CXX_FLAGS_RELEASE "${GENERAL_FLAGS} -O3 -Wl,--no-as-needed")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

if (APPLE)
  include_directories(/usr/local/include)
endif (APPLE)


include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
link_directories(${LIB_DIR})

# source directory
add_subdirectory(src)


