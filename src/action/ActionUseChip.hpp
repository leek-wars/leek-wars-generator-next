#ifndef ACTION_USE_CHIP_HPP
#define ACTION_USE_CHIP_HPP

#include <vector>
#include "../../lib/json.hpp"

#include "Action.hpp"
class Entity;
class Chip;
class Cell;

class ActionUseChip : public Action {
public:
	int caster;
	int cell;
	int chip;
	int success;
	std::vector<int> entities;

	ActionUseChip(Entity* caster, Cell* cell, Chip* chip, int success);

	void set_entities(std::vector<Entity*> entities);

	virtual Json json() const override;
};

#endif
