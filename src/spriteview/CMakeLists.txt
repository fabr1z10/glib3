cmake_minimum_required(VERSION 3.3)


file(GLOB SPRITEVIEW_INCLUDE ${INCLUDE_DIR}/spriteview/*.h)
file(GLOB SPRITEVIEW_SRC *.cpp)


add_executable(spriteview ${SPRITEVIEW_INCLUDE} ${SPRITEVIEW_SRC})
target_compile_features(spriteview PRIVATE cxx_std_14)
target_link_libraries(spriteview ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY}
        ${JPEG_LIBRARIES} gfx)
if(APPLE)
    target_link_libraries (spriteview ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	spriteview DESTINATION ${BIN_DIR})
