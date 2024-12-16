#ifndef VME_ITEM_VARS_H
#define VME_ITEM_VARS_H

#include "vme/item.h"
#include <vector>

enum DISPLAY_TYPE {
    RANDOM,
    TILED,
    TABLE
};

extern DISPLAY_TYPE current_display_type;
extern std::vector<Item> items;
extern std::vector<Item> items_history;
extern Item hovered_item;
extern bool hover_item_valid;

#endif

