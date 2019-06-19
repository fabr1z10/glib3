cmake_minimum_required(VERSION 3.3)


file(GLOB PLATFORMER_INCLUDE ${INCLUDE_DIR}/platformer/*.h ${INCLUDE_DIR}/platformer/components/*.h ${INCLUDE_DIR}/platformer/activities/*.h ${INCLUDE_DIR}/platformer/states/*.h ${INCLUDE_DIR}/platformer/input/*.h)
file(GLOB PLATFORMER_SRC *.cpp components/*.cpp activities/*.cpp states/*.cpp input/*.cpp lua/*.cpp)


add_executable(platformer ${PLATFORMER_INCLUDE} ${PLATFORMER_SRC})

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(platformer ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY}
        ${JPEG_LIBRARIES} gfx)
if(APPLE)
   target_link_libraries (platformer ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	platformer DESTINATION ${BIN_DIR})
