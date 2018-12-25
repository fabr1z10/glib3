cmake_minimum_required(VERSION 3.3)

find_package(Lua REQUIRED)

file(GLOB GFX_INCLUDE ${INCLUDE_DIR}/gfx/*.h ${INCLUDE_DIR}/gfx/lua/*.h ${INCLUDE_DIR}/gfx/components/*.h ${INCLUDE_DIR}/gfx/model3D/*.h
        ${INCLUDE_DIR}/gfx/activities/*.h ${INCLUDE_DIR}/gfx/math/*.h ${INCLUDE_DIR}/gfx/factories/*.h
        ${INCLUDE_DIR}/gfx/entities/*.h ${INCLUDE_DIR}/gfx/states/*.h ${INCLUDE_DIR}/gfx/shader/*.h)
file(GLOB GFX_SOURCE *.cpp lua/*.cpp components/*.cpp activities/*.cpp math/*.cpp factories/*.cpp entities/*.cpp states/*.cpp model3D/*.cpp)

add_library(gfx STATIC ${GFX_INCLUDE} ${GFX_SOURCE})

#target_link_libraries(gfx ${LUA_LIBRARIES})
target_link_libraries(gfx ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES})


install(TARGETS gfx DESTINATION ${LIB_DIR})
