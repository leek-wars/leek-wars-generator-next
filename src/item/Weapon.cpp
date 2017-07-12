#include "Weapon.hpp"

Weapon::Weapon(int id, std::string name, int cost, Attack* attack, int template_id) : Item(id, name, cost, attack, template_id) {
	readonly = true;
}

Weapon::~Weapon() {}

std::ostream& Weapon::print(std::ostream& os) const {
	os << "<Weapon ";
	const LSValue* v = values.at("name");
	v->print(os);
	os << ">";
	return os;
}

std::ostream& Weapon::dump(std::ostream& os, int) const {
	os << "<Weapon ";
	const LSValue* v = values.at("name");
	v->print(os);
	os << ">";
	return os;
}
