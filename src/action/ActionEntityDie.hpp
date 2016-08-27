#ifndef ACTION_ENTITY_DIE
#define ACTION_ENTITY_DIE

#include "Action.hpp"
class Entity;

class ActionEntityDie : public Action {
public:
	int id;
	int killer;

	ActionEntityDie(Entity* leek, Entity* killer);

	virtual Json json() const override;
};

#endif
