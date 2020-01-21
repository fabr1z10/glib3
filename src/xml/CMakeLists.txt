cmake_minimum_required(VERSION 3.3)

file(GLOB XML_INCLUDE ${INCLUDE_DIR}/xml/*.h)
file(GLOB XML_SOURCE *.cpp)

include_directories(${INCLUDE_DIR})

add_library(xml STATIC ${XML_INCLUDE} ${XML_SOURCE})

install(TARGETS xml DESTINATION ${LIB_DIR})
