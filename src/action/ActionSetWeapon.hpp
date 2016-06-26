#ifndef ACTION_SET_WEAPON
#define ACTION_SET_WEAPON

#include "Action.hpp"
class Entity;
class Weapon;

class ActionSetWeapon : public Action {
public:
	int entity;
	int weapon;

	ActionSetWeapon(Entity* entity, const Weapon* weapon);

	virtual Json json() const override;
};

#endif
