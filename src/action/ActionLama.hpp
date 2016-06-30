#ifndef ACTION_LAMA
#define ACTION_LAMA

#include "Action.hpp"
class Entity;

class ActionLama : public Action {
public:
	int caster;

	ActionLama(Entity* caster);

	virtual Json json() const override;
};

#endif
