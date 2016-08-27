#ifndef ACTION_KILL
#define ACTION_KILL

#include "Action.hpp"
class Entity;

class ActionKill : public Action {
public:
	int caster;
	int target;

	ActionKill(Entity* caster, Entity* target);

	virtual Json json() const override;
};

#endif
