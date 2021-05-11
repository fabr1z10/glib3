cmake_minimum_required(VERSION 3.3)
project(example)

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})


pybind11_add_module(example example.cpp rect.cpp funx.cpp)


#file(GENERATE OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_<CONFIG>}/setup.py"
#INPUT "${SRC_DIR}/prova/setup.py.in")
#configure_file(
#        "${SRC_DIR}/prova/setup.py.in"
#        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/setup.py"
#)

configure_file(
    "${SRC_DIR}/prova/install.sh"
    "${BIN_DIR}/install.sh"
)
configure_file(
    "${SRC_DIR}/prova/setup.py.in"
    "${BIN_DIR}/setup.py"
)

target_link_libraries(example PUBLIC monkey)

#add_custom_command(
#    TARGET example
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    "${SRC_DIR}/prova/setup.py.in"
#    "${BIN_DIR}/setup.py"
#)

install(TARGETS example DESTINATION ${BIN_DIR})
#install(CODE "execute_process(COMMAND ${BIN_DIR}/install.sh)")

#INSTALL(CODE "execute_process(COMMAND ${BIN_DIR}/install.sh)")
