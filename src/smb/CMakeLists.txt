cmake_minimum_required(VERSION 3.3)

add_executable(smb
        main.cpp
        factories.cpp
        states/walkside.cpp
        states/walkside3d.cpp
        states/jump2d.cpp
        states/jump3d.cpp
        states/jumpattack.cpp
        states/foewalk.cpp
        states/foechase.cpp
        states/foedead.cpp
        states/ishit.cpp
        states/bounce.cpp
        states/keymove.cpp
        states/keymovef.cpp
        states/koopashell.cpp)

include_directories(${INCLUDE_DIR}  ${PYBIND_INCLUDE_DIR} ${Python_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(smb PUBLIC monkey)

install(TARGETS smb DESTINATION ${BIN_DIR})