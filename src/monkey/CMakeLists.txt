cmake_minimum_required(VERSION 3.3)

file(GLOB MONKEY_SOURCE *.cpp python/*.cpp components/*.cpp activities/*.cpp math/*.cpp factories/*.cpp input/*.cpp#
		math/shapes/*.cpp math/algo/*.cpp math/shapes3d/*.cpp math/algo3d/*.cpp mesh/*.cpp factories/*.cpp entities/*.cpp
		states/*.cpp assets/*.cpp model/*.cpp shader/*.cpp skeletal/*.cpp skeletal/animation/*.cpp)

if (DEFINED USE_BULLET)
  set (MONKEY_SOURCE ${MONKEY_SOURCE} bullet/bulletworld.cpp bullet/rigidbody.cpp bullet/shapefactory.cpp
		  bullet/vehicle.cpp bullet/vehiclefollow.cpp)
endif(DEFINED USE_BULLET)

#set(CMAKE_ENABLE_EXPORTS ON)
add_compile_options(-fvisibility=hidden)
#add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

#if(DEFINED USE_ASSIMP)
#	message("PINOMERDA")
#	add_definitions(-DUSE_ASSIMP)
#	#find_package(ASSIMP REQUIRED)
#endif(DEFINED USE_ASSIMP)

#if(DEFINED USE_BULLET)
#	add_definitions(-DUSE_BULLET)
#endif(DEFINED USE_BULLET)

add_executable(monkey ${MONKEY_SOURCE})
set_target_properties(monkey PROPERTIES ENABLE_EXPORTS ON)



include_directories(${INCLUDE_DIR} ${PYBIND_INCLUDE_DIR} ${Python3_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${YAML_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS})

target_link_libraries(monkey
        ${OPENGL_LIBRARIES} ${Python3_LIBRARIES} glfw
        GLEW::GLEW ${FREETYPE_LIBRARIES} ${YAML_CPP_LIBRARIES}
        ${PNG_LIBRARY} ${JPEG_LIBRARIES} ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARIES} alglib box2d ${BULLET_LIBRARIES})



add_custom_command(
		TARGET monkey POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/glsl
				${CMAKE_CURRENT_BINARY_DIR}/glsl)


#install(TARGETS monkey DESTINATION ${LIB_DIR})
#install(TARGETS monkey DESTINATION lib)
