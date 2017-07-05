#include "Weapon.hpp"

Weapon::Weapon(int id, std::string name, int cost, Attack* attack, int template_id) : Item(id, name, cost, attack, template_id) {
	readonly = true;
}

Weapon::~Weapon() {}

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
