cmake_minimum_required(VERSION 3.10)
project(projek-akhir)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
set(GLAD_SRC ./glad/src/glad.c)
set(GLAD_INC ./glad/include)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	./main.cpp
	./imgui/imgui.cpp
	./imgui/imgui_demo.cpp
	./imgui/imgui_draw.cpp
	./imgui/imgui_tables.cpp
	./imgui/imgui_widgets.cpp
	./imgui/backends/imgui_impl_glfw.cpp
	./imgui/backends/imgui_impl_opengl3.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	./imgui/
	./imgui/backends
	${GLAD_INC}
)
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)
target_sources(${PROJECT_NAME} PRIVATE ${GLAD_SRC})
