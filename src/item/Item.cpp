#include "Item.hpp"

Item::Item(int id, std::string& name, int cost, Attack* attack, int template_id)
	: id(id), name(name), cost(cost), attack(attack), template_id(template_id) {

	native = true;
	refs = 1;

	auto name_val = new ls::LSString(name);
	name_val->native = true;
	name_val->refs = 1;
	addField("name", name_val);

	auto id_val = ls::LSNumber::get(id);
	id_val->native = true;
	id_val->refs = 1;
	addField("id", id_val);

	auto cost_val = ls::LSNumber::get(cost);
	cost_val->native = true;
	cost_val->refs = 1;
	addField("cost", cost_val);
}

Item::~Item() {
	delete values["name"];
	values.erase("name");
}
