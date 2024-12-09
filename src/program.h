#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>

GLFWwindow* opengl_setup();
void imgui_setup(GLFWwindow* window);
void main_loop(GLFWwindow* window);
void inner_main_loop(GLFWwindow* window);
void finalize(GLFWwindow* window);

#endif

