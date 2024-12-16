#ifndef VARS_H
#define VARS_H

#include "utils.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <random>
#include <chrono>

// forward declaration from utils.h
struct rect;

extern GLFWwindow* glfw_window;
constexpr ImGuiWindowFlags common_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				   								 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
extern rect prev_window_data;
extern ImVec2 mouse_pos;
extern float fps;
extern float glyph_size;
constexpr float magic_padding = -13.5;
extern std::random_device rand_dev;
extern std::mt19937 rng;
extern long global_tick;

ImVec2 display_size();
rect get_current_window_data();
void update_prev_window_data();
void init_imgui_stats();
void update_imgui_stats();
std::time_t get_current_time();

#endif

