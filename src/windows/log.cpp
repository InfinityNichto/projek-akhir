#include "windows/log.h"
#include "vme/item_vars.h"

#include <string>

std::string current_buf = "";

void log() {
 	ImVec2 display = display_size();
	ImVec2 next_pos = ImVec2(0, prev_window_data.y);
	ImVec2 next_size = ImVec2(display.x, prev_window_data.h);

	ImGui::SetNextWindowPos(next_pos);
	ImGui::SetNextWindowSize(next_size);
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImGui::Begin("Log", NULL, window_flags);

    text_wrapped("%s", current_buf.c_str());

    ImGui::End();
}
