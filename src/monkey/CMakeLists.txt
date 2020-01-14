cmake_minimum_required(VERSION 3.3)

file(GLOB MONKEY_INCLUDE ${INCLUDE_DIR}/gfx/*.h ${INCLUDE_DIR}/gfx/lua/*.h ${INCLUDE_DIR}/gfx/components/*.h ${INCLUDE_DIR}/gfx/model/*.h
        ${INCLUDE_DIR}/gfx/factories/*.h
        ${INCLUDE_DIR}/gfx/activities/*.h ${INCLUDE_DIR}/gfx/math/*.h ${INCLUDE_DIR}/gfx/factories/*.h
        ${INCLUDE_DIR}/gfx/entities/*.h ${INCLUDE_DIR}/gfx/states/*.h ${INCLUDE_DIR}/gfx/shader/*.h)
file(GLOB MONKEY_SOURCE *.cpp lua/*.cpp components/*.cpp activities/*.cpp math/*.cpp factories/*.cpp entities/*.cpp states/*.cpp model/*.cpp)

add_executable(monkey ${MONKEY_INCLUDE} ${MONKEY_SOURCE})

message(${LUA_INCLUDE_DIR})

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(monkey ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} ${CMAKE_DL_LIBS} alglib)

install(TARGETS monkey DESTINATION ${LIB_DIR})
