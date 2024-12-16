#include "vars.h"

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <random>

GLFWwindow* glfw_window;
ImVec2 prev_window_pos;
ImVec2 prev_window_size;
ImVec2 mouse_pos;
float fps;
ImVec2 glyph_size;

std::random_device rand_dev;
std::mt19937 rng(rand());

std::vector<Item> items = {};
std::vector<Item> items_history = {};

ImVec2 display_size() {
    return ImGui::GetIO().DisplaySize;
}

void update_prev_window_data() {
	prev_window_pos = ImGui::GetWindowPos();
	prev_window_size = ImGui::GetWindowSize();
}

void init_imgui_stats() {
	ImGuiIO io = ImGui::GetIO();
	mouse_pos = io.MousePos;
	fps = io.Framerate;
	glyph_size = ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight());
}

void update_imgui_stats() {
	ImGuiIO io = ImGui::GetIO();
	mouse_pos = io.MousePos;
	fps = io.Framerate;
}
