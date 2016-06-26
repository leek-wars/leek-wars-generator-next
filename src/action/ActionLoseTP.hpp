#ifndef ACTION_LOSE_TP
#define ACTION_LOSE_TP

#include "Action.hpp"
class Entity;

class ActionLoseTP : public Action {
public:
	int target;
	int tp;

	ActionLoseTP(Entity* target, int pt);

	virtual Json json() const override;
};

#endif
