/*
 * Weapon.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: pierre
 */

#include "Weapon.hpp"

Weapon::Weapon(int id, std::string name, int cost, Attack* attack)
	: Item(id, name, cost, attack) {

	readonly = true;
	auto name_val = new ls::LSString(name);
	name_val->native = true;
	name_val->refs = 1;
	addField("name", name_val);
}

Weapon::~Weapon() {
	delete values["name"];
	values.erase("name");
}

int Weapon::getTemplateID() const {
	switch (id) {
		case 37: return 1;
		case 42: return 6;
	}
	return 2;
}

std::ostream& Weapon::print(std::ostream& os) const {
	os << "<Weapon ";
	const LSValue* v = values.at("name");
	v->print(os);
	os << " " << id;
	os << ">";
	return os;
}
