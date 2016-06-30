#ifndef ACTION_VITALITY
#define ACTION_VITALITY

#include "Action.hpp"
#include "../entity/Entity.hpp"

class ActionVitality : public Action {
public:
	int target;
	int life;

	ActionVitality(Entity* target, int life);

	virtual Json json() const override;
};

#endif
