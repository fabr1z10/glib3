cmake_minimum_required(VERSION 3.3)

file(GLOB GFX_SOURCE *.cpp)

add_library(pippolib SHARED ${GFX_INCLUDE} ${GFX_SOURCE})

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

INSTALL(TARGETS pippolib DESTINATION lib)
