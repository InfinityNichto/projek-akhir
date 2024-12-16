#include "imgui.h"
#include "utils.h"
#include "vars.h"
#include "vme/item.h"
#include "vme/item_vars.h"
#include "windows/workspace.h"

#include <string>
#include <ctime>

ImVec2 side_bar_size;

char tmp_newItem_name[64];
std::string tmp_newItem_category[64];

void workspace() {
	side_bar();
	item_display();
	item_info();
}

void side_bar() {
	ImVec2 display = display_size();

	ImGui::SetNextWindowPos(ImVec2(0, prev_window_data.h));
	ImGui::SetNextWindowSize(ImVec2(display.x * 0.15625, display.y - prev_window_data.h));
	ImGui::SetNextWindowBgAlpha(1);

    ImGuiWindowFlags window_flags = common_window_flags;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.16f, 0.16f, 0.16f, 0.5f));

	ImGui::Begin("Side bar", NULL, window_flags);

    separator_heading("Add new item");
    ImGui::Text("new item form here");

    separator_heading("Dummy control");
	if (ImGui::Button("Push dummy item")) {
		Item item = Item();
        item.add_to_items();
	}

	if (ImGui::Button("Pop last item")) {
		items.pop_back();
	}

	ImGui::PopStyleColor(1);
    update_prev_window_data();
    ImGui::End();
}

void write_stats() {
	ImGui::SetCursorPosY(prev_window_data.h - 57);
	ImGui::BeginDisabled();
	ImGui::Text("Mouse position: %s", ImVec2_to_cstr(mouse_pos));
	ImGui::Text("Performance: %.2f FPS", fps);
    ImGui::Text("Tick: %ld/%ld ticks", global_tick, global_tick % (int)fps);
	ImGui::EndDisabled();
}

void item_display() {
	ImVec2 display = display_size();

	ImGui::SetNextWindowPos(ImVec2(prev_window_data.w, prev_window_data.y));
	ImGui::SetNextWindowSize(ImVec2(display.x * 0.625, prev_window_data.h));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.11f, 0.11f, 0.11f, 0.25f));

	ImGui::Begin("Item display", NULL, window_flags);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	for (Item& item : items) {
		item.update();
		item.draw();
	}
	ImGui::PopStyleVar(2);

    draw_grid(25, 1);
	write_stats();

	ImGui::PopStyleColor(1);
	side_bar_size = prev_window_data.size();
	update_prev_window_data();
	ImGui::End();
}

void item_info() {
	ImGui::SetNextWindowPos(ImVec2(prev_window_data.x + prev_window_data.w, prev_window_data.y));
	ImGui::SetNextWindowSize(ImVec2(display_size().x * 0.21875, side_bar_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 0.25f));

	ImGui::Begin("Properties", NULL, window_flags);

    if (hover_item_valid) {
        ImGui::Text("Name: %s", hovered_item.name.c_str());
        ImGui::Text("Category: %s", hovered_item.category.c_str());
        ImGui::Text("Buy price: Rp. %.2f", hovered_item.buy_price);
        ImGui::Text("Sell price: Rp. %.2f", hovered_item.sell_price);
        ImGui::Text("Stock: x%d", hovered_item.stock);
        ImGui::Separator();
        ImGui::Text("Created at: %lds since unix epoch", hovered_item.time_added_unix);
        ImGui::Text("            %s", format_time(hovered_item.time_added_local, "%Y-%m-%d/%H:%M:%S").c_str());
    } else {
        ImGui::BeginDisabled(); ImGui::Text("Hover on an item to see their properties"); ImGui::EndDisabled();
    } hover_item_valid = false;

	ImGui::PopStyleColor(1);
	ImGui::End();
}
