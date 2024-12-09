#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "file.h"

void item_file_exit(GLFWwindow* window) {
	glfwSetWindowShouldClose(window, GLFW_TRUE);	
}

