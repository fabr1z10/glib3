cmake_minimum_required(VERSION 3.3)

file(GLOB GFX_INCLUDE ${INCLUDE_DIR}/gfx/*.h)
file(GLOB GFX_SOURCE *.cpp)

add_library(gfx STATIC ${GFX_INCLUDE} ${GFX_SOURCE})
#target_link_libraries(gfx ${OPENGL_LIBRARIES})


install(TARGETS gfx DESTINATION ${LIB_DIR})
