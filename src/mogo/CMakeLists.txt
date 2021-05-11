cmake_minimum_required(VERSION 3.3)

add_executable(mogo main.cpp)

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(mogo PUBLIC monkey)

install(TARGETS mogo DESTINATION ${BIN_DIR})