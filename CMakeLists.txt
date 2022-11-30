cmake_minimum_required(VERSION 3.7)
project(Voronoi-OpenGL VERSION 1.0.0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



set(HEADERS
	"src/window/window.h"
	"src/utility/apptime.h"
	"src/renderer.h"
	"src/utility/debug.h"
	"src/voronoiseed.h"
	"src/utility/mathutility.h"
	"src/input/inputmanager.h"
)
set(IMPLEMENTATION 
	"src/main.cpp"
	"src/window/window.cpp"
	"src/utility/apptime.cpp"
	"src/renderer.cpp"
	"src/utility/debug.cpp"
	"src/voronoiseed.cpp"
	"src/utility/mathutility.cpp"
	"src/input/inputmanager.cpp"
)

set(LIBS "lib/glad/src/glad.c")

add_subdirectory("lib/glfw-3.3.4")

add_executable(Voronoi-OpenGL ${IMPLEMENTATION} ${HEADERS} ${LIBS})
target_include_directories(Voronoi-OpenGL PRIVATE "src" "lib/glad/include" "lib/glm-0.9.9.8")
target_compile_features(Voronoi-OpenGL PUBLIC cxx_std_17)
set_target_properties(Voronoi-OpenGL PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Voronoi-OpenGL PROPERTIES SOVERSION 1)
target_link_libraries(Voronoi-OpenGL glfw ${CMAKE_DL_LIBS})


