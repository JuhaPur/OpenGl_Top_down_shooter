# Specify minimum supported cmake version and C++ 17
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project (engine)

file(GLOB ENGINE_INC_FILES "./include/*.h")
file(GLOB ENGINE_GRAPHICS_INC_FILES "./include/graphics/*.h")


file(GLOB ENGINE_SRC_FILES "./source/*.cpp")
file(GLOB ENGINE_GRAPHICS_SRC_FILES "./source/graphics/*.cpp")


add_library(engine 
	${ENGINE_INC_FILES} ${ENGINE_GRAPHICS_INC_FILES} 
	${ENGINE_SRC_FILES} 
	${ENGINE_GRAPHICS_SRC_FILES})

	
include_directories("${GLFW_SOURCE_DIR}/deps")

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

target_link_libraries(engine PUBLIC glfw PUBLIC glm)
