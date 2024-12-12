#include <GLFW/glfw3.h>
#include "imgui.h"
#include "vars.h"

void item_file_exit() {
	glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);	
}

