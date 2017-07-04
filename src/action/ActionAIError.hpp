#ifndef ACTION_AI_ERROR
#define ACTION_AI_ERROR

#include "Action.hpp"
class Entity;

class ActionAIError : public Action {
public:
	int id;

	ActionAIError(Entity* target);
	virtual Json json() const override;
};

#endif
