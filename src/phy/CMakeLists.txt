cmake_minimum_required(VERSION 3.3)

#find_package(BLAS)
#find_package(LAPACK)
#find_package(LAPACKE)
find_package(Bullet REQUIRED)

message(STATUS "bullet libs ${BULLET_LIBRARIES}")


add_executable(phy
        main.cpp
        factories.cpp
        rigidbody.cpp
        btshapewrapper.cpp
        bulletengine.cpp)

include_directories(${INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${BULLET_INCLUDE_DIRS})
#include_directories(${BULLET_INCLUDE_DIRS})
#target_link_libraries(phy ${BULLET_LIBRARIES})
target_link_libraries(phy monkey ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES}
        ${BULLET_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES})
 #        ${BULLET_LIBRARIES} gfx)

