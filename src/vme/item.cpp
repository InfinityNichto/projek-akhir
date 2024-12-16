#include "vme/item.h"
#include "vme/item_vars.h"
#include "utils.h"
#include "vars.h"

#include <string>
#include <vector>
#include <ctime>
Item::Item() : name("dummy dummy dummy"), category("dummy dummy dummy"), sc_name("dummy dummy dummy", 9), sc_category("dummy dummy dummy", 9) {
	buy_price = next_real<float>();
    sell_price = next_real<float>();
    stock = next_int<int>();

    time_added_unix = get_current_time();
    time_added_local = as_localtime(time_added_unix);

    unique_id = next_int<int>();
}

Item::Item(std::string name, std::string category, float buy_price, float sell_price, int stock) :
		   name(name), category(category), sell_price(sell_price), buy_price(buy_price), stock(stock), sc_name(this->name, 9), sc_category(this->name, 9) {	
    time_added_unix = get_current_time();
    time_added_local = as_localtime(time_added_unix);

    unique_id = next_int<int>();
}

std::string Item::to_string() const {
	return build_str("(name: ", name, ", category: ", category, ", buy_price", buy_price, ", sell_price: ", sell_price, ", stock: ", stock, ")");
}

// adds a copy to `items` stack
void Item::add_to_items() {
    rect current_data = get_current_window_data();
    start_pos = ImVec2(next_real<float>(current_data.w, current_data.w * 5), next_real<float>(current_data.y, current_data.y + current_data.h));
    items.push_back(*this);
}

void Item::remove_from_items() {
    size_t i = 0;
    for (Item item : items) {
        if (item.unique_id == unique_id) {
            items.erase(items.begin() + i);
            break;
        }
        i++;
    }
}

int Item::get_id() const {
	return unique_id;
}

void Item::update() {
    sc_name.scroll(0.0166);
    sc_category.scroll(0.0083);
}

void Item::draw() const {
	ImGui::SetNextWindowPos(start_pos, ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(65, 65));
	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	
	ImGui::Begin(build_str("vme_item###", unique_id).c_str(), NULL, window_flags);

    rect current_data = get_current_window_data();

	ImGui::Text("%s", sc_name.cstr());
    ImGui::SetCursorPosY(current_data.h * 0.5 - 7); ImGui::Text("%s", sc_category.cstr());
    ImGui::SetCursorPosY(current_data.h - 15); ImGui::Text("x%d", stock);

    ImVec2 bounding_box_tl = ImVec2(current_data.x, current_data.y);
    ImVec2 bounding_box_br = ImVec2(current_data.x + current_data.w, current_data.y + current_data.h);
    if (ImGui::IsMouseHoveringRect(bounding_box_tl, bounding_box_br)) {
        hovered_item = *this;
        hover_item_valid = true;
    }

	ImGui::End();
}
