cmake_minimum_required(VERSION 3.3)

add_executable(scumm
		main.cpp
        activities/walk.cpp
        activities/turn.cpp
        activities/say.cpp
        activities/enableblock.cpp
        components/character.cpp
        components/walkarea.cpp
        factories.cpp
		lua.cpp)

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

target_link_libraries(scumm monkey)
