#include "vars.h"
#include "utils.h"

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <random>

GLFWwindow* glfw_window;
rect prev_window_data {0, 0, 0, 0};
ImVec2 mouse_pos;
float fps;
float glyph_size;
long global_tick = 0;

std::random_device rand_dev;
std::mt19937 rng(rand());

ImVec2 display_size() {
    return ImGui::GetIO().DisplaySize;
}

rect get_current_window_data() {
    return rect(ImGui::GetWindowPos(), ImGui::GetWindowSize());
}

void update_prev_window_data() {
    rect current_data = get_current_window_data();
    prev_window_data = current_data;
}

void init_imgui_stats() {
	ImGuiIO io = ImGui::GetIO();
	mouse_pos = io.MousePos;
	fps = io.Framerate;
	glyph_size = ImGui::GetTextLineHeight();
}

void update_imgui_stats() {
	ImGuiIO io = ImGui::GetIO();
	mouse_pos = io.MousePos;
	fps = io.Framerate;
    global_tick++;
}

// thanks, stack overflow
time_t get_current_time() {
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

