#include "ActionUseChip.hpp"

#include "../entity/Entity.hpp"

ActionUseChip::ActionUseChip(Entity* caster, Cell* cell, Chip* chip, int success) {
	this->caster = caster->id;
	this->cell = cell->id;
	this->chip = chip->id;
	this->success = success;
}

void ActionUseChip::set_entities(vector<Entity*> entities) {
	for (auto e : entities) {
		this->entities.push_back(e->id);
	}
}

Json ActionUseChip::json() const {
	return {(int) ActionType::USE_CHIP, caster, cell, chip, success, entities};
}
