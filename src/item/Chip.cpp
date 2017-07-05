#include "Chip.hpp"

Chip::Chip(int id, std::string name, int cost, int cooldown, bool team_cooldown, int initial_cooldown, Attack* attack, int template_id)
	: Item(id, name, cost, attack, template_id) {

	this->cooldown = cooldown;
	this->team_cooldown = team_cooldown;
	this->initial_cooldown = initial_cooldown;

	readonly = true;
}

Chip::~Chip() {}

std::ostream& Chip::print(std::ostream& os) const {
	os << "<Chip ";
	const LSValue* v = values.at("name");
	v->print(os);
	os << ">";
	return os;
}
