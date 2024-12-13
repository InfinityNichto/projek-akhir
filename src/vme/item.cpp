#include "vme/item.h"
#include "utils.h"
#include "vars.h"

#include <string>

Item::Item() : name("dummy"), category("dummy") {
	unique_id = next_int<int>();
	// log_tty("%d", unique_id);
}
Item::Item(std::string name, std::string category, float buy_price, float sell_price, int stock) :
		   name(name), category(category), sell_price(sell_price), buy_price(buy_price), stock(stock) {
	unique_id = next_int<int>();
	// log_tty("%d", unique_id);
}

std::string Item::to_string() const {
	return build_str("(name: ", name, ", category: ", category, ", buy_price", buy_price, ", sell_price: ", sell_price, ", stock: ", stock, ")");
}

void Item::draw() const {
	ImGui::SetNextWindowPos(ImVec2(250, 250), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(65, 65));
	ImGuiWindowFlags window_flags = common_window_flags & ~(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	
	ImGui::Begin(build_str("vme_item###", unique_id).c_str(), NULL, window_flags);

	ImGui::Text("%s", name.c_str());
	ImGui::Text("%c", category[0]);
	ImGui::Text("%dx", stock);

	ImGui::End();
}