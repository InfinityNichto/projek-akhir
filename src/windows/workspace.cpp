#include "imgui.h"
#include "utils.h"
#include "vars.h"
#include "windows/workspace.h"

void workspace() {
	side_bar();
	item_display();
	item_info();
}

void side_bar() {
	ImVec2 display = display_size();

	ImGui::SetNextWindowPos(ImVec2(0, prev_window_size.y));
	ImGui::SetNextWindowSize(ImVec2(200, display.y - prev_window_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.16f, 0.16f, 0.16f, 0.5f));

	ImGui::Begin("side_bar", NULL, common_window_flags);

	ImGui::PopStyleColor(1);
	update_prev_window_data();
	ImGui::End();
}

void item_display() {
	ImGui::SetNextWindowPos(ImVec2(prev_window_size.x, prev_window_pos.y));
	ImGui::SetNextWindowSize(ImVec2(800, prev_window_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.11f, 0.11f, 0.11f, 0.25f));

	ImGui::Begin("item_display", NULL, common_window_flags);

	ImGui::PopStyleColor(1);
	update_prev_window_data();
	ImGui::End();
}

void item_info() {
	ImGui::SetNextWindowPos(ImVec2(prev_window_pos.x + prev_window_size.x, prev_window_pos.y));
	ImGui::SetNextWindowSize(ImVec2(280, prev_window_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 0.25f));

	ImGui::Begin("item_info", NULL, common_window_flags);

	ImGui::PopStyleColor(1);
	ImGui::End();
}
