#ifndef VME_ITEM_H
#define VME_ITEM_H

#include <string>

struct item {
	int unique_id;

	std::string name;
	std::string category;
	float buy_price;
	float sell_price;
	int stock;

	item();
	item(std::string name, std::string category, float buy_price, float sell_price, int stock);

	std::string to_string() const;
	void display() const;
	void draw();
};

#endif

