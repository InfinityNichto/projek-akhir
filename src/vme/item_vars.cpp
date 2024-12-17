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

std::vector<transaction> transactions = {};
float transaction::total_saving = 0;
float transaction::total_expense = 0;
transaction::transaction(Item item) : item(item), current_saving(0), current_expense(0) {}

std::string transaction::to_string() {
    return build_str("[item: ", item.to_string().c_str(), " current saving: Rp. ", current_saving, "current expense: Rp. ", current_expense, "]");
}

void transaction::compute_expense() {
    total_saving -= item.buy_price * item.stock;
    total_expense += item.buy_price * item.stock;

    current_saving = total_saving;
    current_expense = total_expense;
}

void transaction::compute_gain() {
    total_saving += item.sell_price * item.stock;

    current_saving = total_saving;
    current_expense = total_expense;
}

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
float new_total_saving = 0;
