cmake_minimum_required(VERSION 3.3)

file(GLOB PLATFORMER_INCLUDE ${INCLUDE_DIR}/platformer/*.h ${INCLUDE_DIR}/platformer/components/*.h ${INCLUDE_DIR}/platformer/activities/*.h ${INCLUDE_DIR}/platformer/states/*.h)
file(GLOB PLATFORMER_SRC *.cpp components/*.cpp activities/*.cpp states/*.cpp)


add_executable(platformer ${PLATFORMER_INCLUDE} ${PLATFORMER_SRC})
target_link_libraries(platformer ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} gfx)
if(APPLE)
   target_link_libraries (monkey ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	platformer DESTINATION ${BIN_DIR})
