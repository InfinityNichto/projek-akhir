#include "vme/item.h"
#include "utils.h"
#include "vars.h"

#include <string>
#include <functional>

item::item() : name("dummy") : category("dummy") {
	// thanks, stack overflow
	unique_id = std::hash<const void*>{}(this);
}
item::item(std::string name, std::string category, float buy_price, float sell_price, int stock) :
		   name(name), category(category), sell_price(sell_price), buy_price(buy_price), stock(stock) {
	unique_id = std::hash,const void*>{}(this);
}

std::string item::to_string() const {
	return build_str("(name: ", name, ", category: ", category, ", buy_price", buy_price, ", sell_price: ", sell_price, ", stock: " << stock << ")");
}

void draw() const {
	ImGui::Begin(build_cstr("vme_item##", unique_id)
}

