cmake_minimum_required(VERSION 3.5)

project(Game_engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)

#option(FREETYPE_BUILD_EXAMPLES "" OFF)
#option(FREETYPE_BUILD_DOCS "" OFF)
#option(FREETYPE_BUILD_TESTS "" OFF)
option(FT_WITH_HARFBUZZ "" OFF)


# Specify the stb-image include directory
include_directories("ext/stb-master")
include_directories("ext/kgfw/include")
include_directories(${GLFW_INCLUDE_DIRS})
include_directories("engine/include")
include_directories(".")
include_directories("ext/freetype-2.12.1/include")




# add_subdirectorys to be CMaked
add_subdirectory(ext/glfw-3.3.8)
add_subdirectory(ext/glm-master)
add_subdirectory(ext/kgfw)
add_subdirectory(ext/freetype-2.12.1)
add_subdirectory(engine)

include_directories("${GLFW_SOURCE_DIR}/deps")
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c")

file(GLOB GAME_SRC_FILES "./game/*.cpp")
file(GLOB GAME_INC_FILES "./game/*.h")

add_executable(main ${GAME_SRC_FILES} ${GAME_INC_FILES}
${GLAD_GL} ${PROJECT_SOURCE_DIR}/ext/glfw-3.3.8/deps/glad/gl.h 
${PROJECT_SOURCE_DIR}/ext/glfw-3.3.8/deps/glad_gl.c)

target_link_libraries(main PUBLIC engine kgfw glfw freetype) #${FREETYPE_LIBRARIES}
# Sandbox executables
#add_executable (test_ecs  game/Transform.cpp  sandboxes/test_ecs.cpp engine/source/graphics/Shader.cpp ${GLAD_GL})
#add_executable (test_audio_ecs game/Transform.cpp sandboxes/test_audio_ecs.cpp engine/source/graphics/Shader.cpp ${GLAD_GL} )
