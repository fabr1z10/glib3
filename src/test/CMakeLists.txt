cmake_minimum_required(VERSION 3.3)

file(GLOB TEST_INCLUDE ${INCLUDE_DIR}/test/*.h)
file(GLOB TEST_SRC *.cpp)

MESSAGE("${OPENGL_LIBRARIES}")
include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

add_executable(unittest ${TEST_INCLUDE} ${TEST_SRC})
target_link_libraries(unittest ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} gfx )
if(APPLE)
   target_link_libraries (unittest ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	unittest DESTINATION ${BIN_DIR})
