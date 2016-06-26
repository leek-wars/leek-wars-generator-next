#ifndef ACTION_USE_WEAPON
#define ACTION_USE_WEAPON

#include <vector>
#include "Action.hpp"
class Entity;
class Cell;
class Weapon;

class ActionUseWeapon : public Action {
public:
	int caster;
	int cell;
	int weapon;
	int success;
	std::vector<int> entities;

	ActionUseWeapon(Entity* caster, Cell* cell, const Weapon* weapon, int success);

	void set_entities(std::vector<Entity*> entities);

	virtual Json json() const override;
};

#endif
