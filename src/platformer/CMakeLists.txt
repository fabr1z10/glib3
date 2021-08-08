cmake_minimum_required(VERSION 3.3)


file(GLOB PLATFORMER_INCLUDE states/*.h)
file(GLOB PLATFORMER_SOURCE states/*.cpp extend.cpp walkanim.cpp)

add_library(platformer SHARED ${PLATFORMER_INCLUDE} ${PLATFORMER_SOURCE})

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python3_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(platformer PUBLIC monkey)

