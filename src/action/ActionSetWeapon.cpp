#include "ActionSetWeapon.hpp"

#include "../entity/Entity.hpp"

ActionSetWeapon::ActionSetWeapon(Entity* entity, const Weapon* weapon) {
	this->entity = entity->id;
	this->weapon = weapon->getTemplateID();
	std::cout << "ActionSetWeapon::ctor " << weapon->id << std::endl;
}

Json ActionSetWeapon::json() const {
	return {(int) ActionType::SET_WEAPON, entity, weapon};
}
