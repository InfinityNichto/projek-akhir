#ifndef VARS_H
#define VARS_H

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <random>

extern GLFWwindow* glfw_window;
constexpr ImGuiWindowFlags common_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				   								 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
extern ImVec2 prev_window_pos;
extern ImVec2 prev_window_size;
extern ImVec2 mouse_pos;
extern float fps;
extern ImVec2 glyph_size;
constexpr float magic_padding = -13.5;
extern std::random_device rand_dev;
extern std::mt19937 rng;

ImVec2 display_size();
void update_prev_window_data();
void init_imgui_stats();
void update_imgui_stats();

#endif

