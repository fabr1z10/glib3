cmake_minimum_required(VERSION 3.3)

file(GLOB MONKEY_INCLUDE ${INCLUDE_DIR}/monkey/*.h)
file(GLOB MONKEY_SRC *.cpp)

#find_package(Lua REQUIRED)

add_executable(monkey ${MONKEY_INCLUDE} ${MONKEY_SRC})
target_link_libraries(monkey ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} gfx graph)
if(APPLE)
   target_link_libraries (monkey ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	monkey DESTINATION ${BIN_DIR})
