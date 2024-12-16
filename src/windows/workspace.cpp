#include "imgui.h"
#include "utils.h"
#include "vars.h"
#include "vme/item.h"
#include "windows/workspace.h"

ImVec2 side_bar_size;

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

	ImGui::Begin("Side bar", NULL, window_flags);

	if (ImGui::Button("Push dummy item")) {
		Item::items.push_back(Item());
	}

	if (ImGui::Button("Pop last item")) {
		Item::items.pop_back();
	}

	ImGui::PopStyleColor(1);
	update_prev_window_data();
	ImGui::End();
}

void write_stats() {
	ImGui::SetCursorPosY(prev_window_size.y - 38);
	ImGui::BeginDisabled();
	ImGui::Text("Mouse position: %s", ImVec2_to_cstr(mouse_pos));
	ImGui::Text("Performance: %.2f FPS", fps);
	ImGui::EndDisabled();
}

void item_display() {
	ImVec2 display = display_size();

	ImGui::SetNextWindowPos(ImVec2(prev_window_size.x, prev_window_pos.y));
	ImGui::SetNextWindowSize(ImVec2(800, prev_window_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.11f, 0.11f, 0.11f, 0.25f));

	ImGui::Begin("Item display", NULL, window_flags);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	for (Item item : Item::items) {
		item.update();
		item.draw();
	}
	ImGui::PopStyleVar(2);

	draw_grid(25, 1);
	write_stats();

	ImGui::PopStyleColor(1);
	side_bar_size = prev_window_size;
	update_prev_window_data();
	ImGui::End();
}

void item_info() {
	ImGui::SetNextWindowPos(ImVec2(prev_window_pos.x + prev_window_size.x, prev_window_pos.y));
	ImGui::SetNextWindowSize(ImVec2(280, side_bar_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 0.25f));

	ImGui::Begin("Properties", NULL, window_flags);

	ImGui::PopStyleColor(1);
	ImGui::End();
}
