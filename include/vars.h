#ifndef VARS_H
#define VARS_H

#include "imgui.h"
#include <GLFW/glfw3.h>

extern GLFWwindow* glfw_window;
constexpr ImGuiWindowFlags common_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				   								 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
extern ImVec2 prev_window_pos;
extern ImVec2 prev_window_size;
constexpr float magic_padding = -13.5;

ImVec2 display_size();
void update_prev_window_data();

#endif

