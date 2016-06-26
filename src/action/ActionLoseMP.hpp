#ifndef ACTION_LOSE_MP
#define ACTION_LOSE_MP

#include "Action.hpp"
class Entity;

class ActionLoseMP : public Action {
public:
	int target;
	int mp;

	ActionLoseMP(Entity* target, int mt);

	virtual Json json() const override;
};

#endif
