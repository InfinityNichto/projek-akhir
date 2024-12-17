#include "vme/item.h"
#include "vme/item_vars.h"

#include <string>
#include <vector>

DISPLAY_TYPE current_display_type = DISPLAY_TYPE::RANDOM;
Item* selected_item;
Item hovered_item;
bool hover_item_valid = false;
std::vector<Item> items = {};
std::vector<Item> items_history = {};
std::unordered_map<std::string, ImVec4> category_color_map;
ImVec4 rgb_selected_color = ImVec4(1, 0, 0, 1);
size_t rgb_ptr = 0;
ImVec2 next_start_pos;

std::string display_type_to_string(DISPLAY_TYPE type) {
	switch (type) {
	  case RANDOM: return "Randomized";
	  case TILED: return "Tiled";
	  case TABLE: return "Tabulated";
	  default: return "Unknown";
	}
}

char new_item_name[128] = "";
char new_item_category[64] = "";
float new_item_buy_price = 0;
float new_item_sell_price = 0;
int new_item_stock = 0;

