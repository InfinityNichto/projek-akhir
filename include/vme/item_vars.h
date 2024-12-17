#ifndef VME_ITEM_VARS_H
#define VME_ITEM_VARS_H

#include "vme/item.h"
#include "imgui.h"
#include <string>
#include <vector>
#include <unordered_map>

enum DISPLAY_TYPE {
    RANDOM = 0,
    TILED = 1,
    TABLE = 2
};

std::string display_type_to_string(DISPLAY_TYPE type);

extern DISPLAY_TYPE current_display_type;
extern std::vector<Item> items;
extern std::vector<Item> items_history;
extern Item hovered_item;
extern Item* selected_item;
extern ImVec4 rgb_selected_color;
extern size_t rgb_ptr;
extern ImVec2 next_start_pos;
extern bool hover_item_valid;
extern char new_item_name[128];
extern char new_item_category[64];
extern float new_item_buy_price;
extern float new_item_sell_price;
extern int new_item_stock;
extern std::unordered_map<std::string, ImVec4> category_color_map;

#endif

