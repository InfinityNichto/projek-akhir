#include "vme/item.h"
#include "vme/item_vars.h"
#include <vector>

DISPLAY_TYPE current_display_type = DISPLAY_TYPE::RANDOM; 
Item hovered_item;
bool hover_item_valid = false;
std::vector<Item> items = {};
std::vector<Item> items_history = {};

