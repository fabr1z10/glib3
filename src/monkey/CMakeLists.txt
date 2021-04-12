cmake_minimum_required(VERSION 3.3)

file(GLOB MONKEY_INCLUDE ${INCLUDE_DIR}/gfx/*.h ${INCLUDE_DIR}/gfx/lua/*.h ${INCLUDE_DIR}/gfx/components/*.h ${INCLUDE_DIR}/gfx/model/*.h
        ${INCLUDE_DIR}/gfx/factories/*.h
        ${INCLUDE_DIR}/gfx/activities/*.h ${INCLUDE_DIR}/gfx/math/*.h ${INCLUDE_DIR}/gfx/factories/*.h
        ${INCLUDE_DIR}/gfx/entities/*.h ${INCLUDE_DIR}/gfx/states/*.h ${INCLUDE_DIR}/gfx/shader/*.h)
file(GLOB MONKEY_SOURCE *.cpp lua/*.cpp python/*.cpp components/*.cpp activities/*.cpp math/*.cpp factories/*.cpp input/*.cpp
		math/shapes/*.cpp math/algo/*.cpp math/shapes3d/*.cpp math/algo3d/*.cpp mesh/*.cpp factories/*.cpp entities/*.cpp states/*.cpp assets/*.cpp model/*.cpp shader/*.cpp
		skeletal/*.cpp skeletal/animation/*.cpp)

#set(CMAKE_ENABLE_EXPORTS ON)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

add_library(monkey SHARED ${MONKEY_INCLUDE} ${MONKEY_SOURCE})

#message(${LUA_INCLUDE_DIR})

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS}
		${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${YAML_INCLUDE_DIRS})

target_link_libraries(monkey
    ${OPENGL_LIBRARIES} ${Python_LIBRARIES} glfw
    GLEW::GLEW ${FREETYPE_LIBRARIES} ${YAML_CPP_LIBRARIES}
    ${PNG_LIBRARY} ${JPEG_LIBRARIES} ${CMAKE_DL_LIBS}
    ${Boost_SYSTEM_LIBRARY} alglib)


add_custom_command(
		TARGET monkey POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
				${CMAKE_SOURCE_DIR}/src/config.json
				${BIN_DIR}/config.json)


#install(TARGETS monkey DESTINATION ${LIB_DIR})
install(TARGETS monkey DESTINATION lib)
