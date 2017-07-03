#ifndef ACTION_ENTITY_TURN
#define ACTION_ENTITY_TURN

#include "Action.hpp"
class Entity;

class ActionEntityTurn : public Action {
public:
	int id;
	int tp;
	int mp;

	ActionEntityTurn(Entity* entity);

	virtual Json json() const override;
};

#endif
