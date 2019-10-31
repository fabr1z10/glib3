cmake_minimum_required(VERSION 3.3)

find_package(BLAS)
find_package(LAPACK)
find_package(LAPACKE)
find_package(Bullet REQUIRED)

if(LAPACK_FOUND AND BLAS_FOUND)
   set(lapackblas_libraries ${BLAS_LIBRARIES} ${LAPACKE_LIBRARIES})
    message ("FOFOFOFOFO")
endif()

file(GLOB PHY_INCLUDE ${INCLUDE_DIR}/phy/*.h ${INCLUDE_DIR}/phy/components/*.h ${INCLUDE_DIR}/phy/activities/*.h ${INCLUDE_DIR}/phy/states/*.h)
file(GLOB PHY_SRC *.cpp components/*.cpp activities/*.cpp states/*.cpp lua/*.cpp)




add_executable(phy ${PHY_INCLUDE} ${PHY_SRC})
target_link_libraries(phy ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES} ${PNG_LIBRARY} ${JPEG_LIBRARIES} ${lapackblas_libraries} gfx)
if(APPLE)
   target_link_libraries (phy ${BZ2_LIB} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CV_LIBRARY})
endif(APPLE)
install(TARGETS	phy DESTINATION ${BIN_DIR})
