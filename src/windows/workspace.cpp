#include "imgui.h"
#include "utils.h"
#include "vars.h"
#include "vme/item.h"
#include "vme/item_vars.h"
#include "windows/workspace.h"
#include "windows/log.h"

#include <string>
#include <ctime>

ImVec2 side_bar_size;

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

    separator_heading("Finances");
    ImGui::TextUnformatted("Total saving: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputFloat("##vme_total_saving_input", &new_total_saving); ImGui::PopItemWidth();
    if (ImGui::Button("Submit##vme_finances")) {
        transaction::total_saving = new_total_saving;
        current_buf += build_str("total saving is now: Rp. ", transaction::total_saving, "\n");
        log_tty("%s", build_str("total saving is now: Rp. ", transaction::total_saving).c_str());
    }

    if (ImGui::Button("Log all transactions")) {
        for (transaction t : transactions) {
            current_buf += build_str(t.to_string().c_str(), "\n");
            log_tty("%s", t.to_string().c_str());
        }
    }

    separator_heading("Add new item");
	ImGui::TextUnformatted("Name: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputText("##vme_name_input", new_item_name, sizeof(new_item_name)); ImGui::PopItemWidth();
	ImGui::TextUnformatted("Category: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputText("##vme_category_input", new_item_category, sizeof(new_item_category)); ImGui::PopItemWidth();
	ImGui::TextUnformatted("Buy price: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputFloat("##vme_buy_price_input", &new_item_buy_price); ImGui::PopItemWidth(); 
	ImGui::TextUnformatted("Sell price: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputFloat("##vme_sell_price_input", &new_item_sell_price); ImGui::PopItemWidth(); 
	ImGui::TextUnformatted("Stock: "); ImGui::SameLine(0, 0);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x); ImGui::InputInt("##vme_stock_input", &new_item_stock); ImGui::PopItemWidth();
	if (ImGui::Button("Submit")) {
		Item item = Item(std::string(new_item_name), std::string(new_item_category), new_item_buy_price, new_item_sell_price, new_item_stock);
		item.add_to_items();
	}

	separator_heading("Controls");
	if (ImGui::Button("Sell selected item")) {
		if (selected_item != nullptr) {
			selected_item->remove_from_items();
			selected_item = nullptr;
		}
	}

	if (ImGui::Button("Push dummy item")) {
		Item item = Item();
        item.add_to_items();
	}

	if (ImGui::Button("Sell last item")) {
		if (items.size() > 0) items[items.size() - 1].remove_from_items();
	}

	if (ImGui::Button("Switch display mode")) {
		current_display_type = static_cast<DISPLAY_TYPE>((static_cast<int>(current_display_type) + 1) % 3);
	} text_hover_formatted("Current display type: %s", display_type_to_string(current_display_type).c_str());


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
	ImVec2 next_pos = ImVec2(prev_window_data.w, prev_window_data.y);
	ImVec2 next_size = ImVec2(display.x * 0.625, prev_window_data.h);

	ImGui::SetNextWindowPos(next_pos);
	ImGui::SetNextWindowSize(next_size);
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.11f, 0.11f, 0.11f, 0.25f));

	ImGui::Begin("Item display", NULL, window_flags);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	size_t i = 0, padding = 5;
	for (Item& item : items) {
		if (current_display_type == DISPLAY_TYPE::TILED) {
			size_t items_per_row = (next_size.x - padding) / (65 + padding);
			size_t row = i / items_per_row, col = i % items_per_row;
			next_start_pos = ImVec2(next_pos.x + padding + col * (65 + padding), next_pos.y + 25 + row * (65 + padding));
		}

		item.update();
		item.draw();
		i++;
	}
	ImGui::PopStyleVar(2);

    draw_grid(25, 1);
	write_stats();

	ImGui::PopStyleColor(1);
	side_bar_size = prev_window_data.size();
	update_prev_window_data();
	ImGui::End();
}

void write_item_info(Item item) {
    text_wrapped("Name: %s", hovered_item.name.c_str());
    text_wrapped("Category: %s", hovered_item.category.c_str());
    text_wrapped("Buy price: Rp. %.2f", hovered_item.buy_price);
    text_wrapped("Sell price: Rp. %.2f", hovered_item.sell_price);
	text_wrapped("Stock: x%d", hovered_item.stock);
    text_wrapped("Created at: %lds since unix epoch", hovered_item.time_added_unix);
    text_wrapped("            %s", format_time(hovered_item.time_added_local, "%Y-%m-%d/%H:%M:%S").c_str());
}

void item_info() {
	ImGui::SetNextWindowPos(ImVec2(prev_window_data.x + prev_window_data.w, prev_window_data.y));
	ImGui::SetNextWindowSize(ImVec2(display_size().x * 0.21875, side_bar_size.y));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 0.25f));

	ImGui::Begin("Properties", NULL, window_flags);

	separator_heading("Hovered item properties");
    if (hover_item_valid) write_item_info(hovered_item);
    else { ImGui::BeginDisabled(); text_wrapped("Hover on an item to see their properties"); ImGui::EndDisabled(); }
    hover_item_valid = false;

	separator_heading("Selected item properties");
	if (selected_item != nullptr) write_item_info(*selected_item);
	else { ImGui::BeginDisabled(); text_wrapped("Selected item properties will appear here"); ImGui::EndDisabled(); }

	ImGui::PopStyleColor(1);
	ImGui::End();
}
