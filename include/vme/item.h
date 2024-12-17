#ifndef VME_ITEM_H
#define VME_ITEM_H

#include "utils.h"
#include <string>
#include <vector>
#include <chrono>

struct Item {
private:
	scrolling_text sc_name;
    scrolling_text sc_category;
	size_t char_limit;
    ImVec2 start_pos;
	ImVec4 border_color;
	int unique_id;

public:
	std::string name;
	std::string category;
	float buy_price;
	float sell_price;
	int stock;
    
    std::time_t time_added_unix;
    std::tm time_added_local;

	Item();
	Item(std::string name, std::string category, float buy_price, float sell_price, int stock);

    void add_to_items();
    void remove_from_items();
	std::string to_string() const;
	int get_id() const;
	void update();
	void draw();
};

#endif

