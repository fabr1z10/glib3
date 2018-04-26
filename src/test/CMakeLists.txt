cmake_minimum_required(VERSION 3.3)

add_executable(unittest main.cpp)
target_link_libraries(unittest graph)

install(TARGETS	unittest DESTINATION ${BIN_DIR})
