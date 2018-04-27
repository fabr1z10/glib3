cmake_minimum_required(VERSION 3.3)

file(GLOB TEST_INCLUDE ${INCLUDE_DIR}/test/*.h)

add_executable(unittest ${TEST_INCLUDE} main.cpp)
target_link_libraries(unittest graph)

install(TARGETS	unittest DESTINATION ${BIN_DIR})
