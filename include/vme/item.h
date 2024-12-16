#ifndef VME_ITEM_H
#define VME_ITEM_H

#include "utils.h"
#include <string>
#include <vector>

struct Item {
private:
	scrolling_text sc_name;
	size_t char_limit;
	int unique_id;

public:
	static std::vector<Item> items;
	static std::vector<Item> items_history;

	std::string name;
	std::string category;
	float buy_price;
	float sell_price;
	int stock;

	Item();
	Item(std::string name, std::string category, float buy_price, float sell_price, int stock);

	std::string to_string() const;
	int get_id();
	void update();
	void draw() const;
};

#endif

