#ifndef ACTION_END_TURN
#define ACTION_END_TURN

#include "Action.hpp"
class Entity;

class ActionEndTurn : public Action {
public:
	int target;
	int tp;
	int mp;
	int strength;
	int magic;

	ActionEndTurn(Entity* target);

	virtual Json json() const override;
};

#endif
