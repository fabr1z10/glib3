cmake_minimum_required(VERSION 3.3)
project(example)

include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR})


pybind11_add_module(example example.cpp rect.cpp)

target_link_libraries(example PUBLIC monkey)