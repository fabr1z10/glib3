cmake_minimum_required(VERSION 3.3)

add_executable(smb
        main.cpp
        factories.cpp
        states/platformerstate.cpp
        states/walkside.cpp
        states/jump2d.cpp
        states/foewalk.cpp
        states/foedead.cpp
        states/koopashell.cpp)

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(smb monkey)
