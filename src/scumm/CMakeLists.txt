cmake_minimum_required(VERSION 3.3)


file(GLOB SCUMM_INCLUDE activities/*.h components/*.h)
file(GLOB SCUMM_SOURCE activities/*.cpp components/*.cpp extend.cpp)

add_library(scumm SHARED ${SCUMM_INCLUDE} ${SCUMM_SOURCE})

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python3_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(scumm PUBLIC monkey)

