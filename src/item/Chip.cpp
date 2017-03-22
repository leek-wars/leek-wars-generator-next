/*
 * Chip.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: pierre
 */

#include "Chip.hpp"

Chip::Chip(int id, std::string&& name, int cost, int cooldown,
		bool team_cooldown, int initial_cooldown, Attack&& attack)
	: Item(id, name, cost, attack) {

	this->cooldown = cooldown;
	this->team_cooldown = team_cooldown;
	this->initial_cooldown = initial_cooldown;

	readonly = true;
	auto name_val = new ls::LSString(name);
	name_val->native = true;
	addField("name", name_val);
}

Chip::~Chip() {}

std::ostream& Chip::print(std::ostream& os) const {
	os << "<Chip ";
	const LSValue* v = values.at("name");
	v->print(os);
	os << ">";
	return os;
}
