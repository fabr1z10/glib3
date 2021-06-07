cmake_minimum_required(VERSION 3.3)


file(GLOB RACER_INCLUDE activities/*.h components/*.h)
file(GLOB RACER_SOURCE activities/*.cpp components/*.cpp extend.cpp)

add_library(racer SHARED ${RACER_INCLUDE} ${RACER_SOURCE})

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python3_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(racer PUBLIC monkey)

