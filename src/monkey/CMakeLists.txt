cmake_minimum_required(VERSION 3.3)

file(GLOB MONKEY_INCLUDE ${INCLUDE_DIR}/monkey/*.h ${INCLUDE_DIR}/monkey/components/*.h ${INCLUDE_DIR}/monkey/activities/*.h)
file(GLOB MONKEY_SRC *.cpp components/*.cpp activities/*.cpp)

#find_package(Lua REQUIRED)

add_executable(monkey ${MONKEY_INCLUDE} ${MONKEY_SRC})

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(monkey glm ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} gfx alglib)
if(APPLE)
   target_link_libraries (monkey ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	monkey DESTINATION ${BIN_DIR})
