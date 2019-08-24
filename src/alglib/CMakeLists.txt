cmake_minimum_required(VERSION 3.3)

file(GLOB GFX_INCLUDE ${INCLUDE_DIR}/alglib/*.h )
file(GLOB GFX_SOURCE *.cpp)

add_library(alglib STATIC ${GFX_INCLUDE} ${GFX_SOURCE})

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

install(TARGETS alglib DESTINATION ${LIB_DIR})
