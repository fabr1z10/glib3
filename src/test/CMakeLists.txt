cmake_minimum_required(VERSION 3.3)

file(GLOB TEST_INCLUDE ${INCLUDE_DIR}/test/*.h)
file(GLOB TEST_SRC *.cpp)

MESSAGE("${OPENGL_LIBRARIES}")

add_executable(unittest ${TEST_INCLUDE} ${TEST_SRC})
target_link_libraries(unittest ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} gfx xml )

install(TARGETS	unittest DESTINATION ${BIN_DIR})
