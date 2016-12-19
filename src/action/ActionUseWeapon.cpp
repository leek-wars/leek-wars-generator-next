#include "ActionUseWeapon.hpp"

#include "../entity/Entity.hpp"

ActionUseWeapon::ActionUseWeapon(Entity* caster, Cell* cell, const Weapon* weapon, int success) {
	this->caster = caster->id;
	this->cell = cell->id;
	this->weapon = weapon->getTemplateID();
	this->success = success;
}

void ActionUseWeapon::set_entities(std::vector<Entity*> entities) {
	for (auto e : entities) {
		this->entities.push_back(e->id);
	}
}

Json ActionUseWeapon::json() const {
	return {(int) ActionType::USE_WEAPON, caster, cell, weapon, success, entities};
}
