#ifndef ACTION_HEAL
#define ACTION_HEAL

#include "Action.hpp"
class Entity;

class ActionHeal : public Action {
public:
	int target;
	int life;

	ActionHeal(Entity* target, int life);

	virtual Json json() const override;
};

#endif
