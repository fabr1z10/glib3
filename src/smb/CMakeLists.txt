cmake_minimum_required(VERSION 3.3)

add_library(smb SHARED
        states/platformerstate.cpp
        states/walkside.cpp
        factories.cpp)

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

