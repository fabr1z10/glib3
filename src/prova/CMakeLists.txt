cmake_minimum_required(VERSION 3.3)
project(example)

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})


pybind11_add_module(example example.cpp rect.cpp funx.cpp)

configure_file(
        "${SRC_DIR}/prova/setup.py.in"
        "${CMAKE_CURRENT_BINARY_DIR}/setup.py"
)

configure_file(
        "${SRC_DIR}/prova/install.sh"
        "${BIN_DIR}/install.sh"
)
target_link_libraries(example PUBLIC monkey)

#install(TARGETS example DESTINATION ${BIN_DIR})
INSTALL(CODE "execute_process(COMMAND ${BIN_DIR}/install.sh)")
