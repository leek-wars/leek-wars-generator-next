#ifndef ACTION_START_FIGHT
#define ACTION_START_FIGHT

#include "Action.hpp"
class Entity;

class ActionStartFight : public Action {
public:

	ActionStartFight();

	virtual Json json() const override;
};

#endif
