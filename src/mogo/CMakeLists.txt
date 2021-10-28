cmake_minimum_required(VERSION 3.3)

add_executable(mogo main.cpp)

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python3_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(mogo PUBLIC monkey)

install(TARGETS mogo DESTINATION ${BIN_DIR})

message("PALOEN")

add_custom_target(copy_assets
		COMMAND rsync -ra "${CMAKE_SOURCE_DIR}/glsl" "${CMAKE_CURRENT_BINARY_DIR}")
add_dependencies(mogo copy_assets)

#add_custom_command(copy_assets
#		COMMAND rsync
#		ARGS -ra "${CMAKE_SOURCE_DIR}/glsl" "${CMAKE_CURRENT_BINARY_DIR}")

