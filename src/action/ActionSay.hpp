#ifndef ACTION_SAY_HPP
#define ACTION_SAY_HPP

#include "Action.hpp"
class Entity;

class ActionSay : public Action {
public:
	int entity;
	std::string message;

	ActionSay(Entity* leek, std::string& message);

	virtual Json json() const override;
};

#endif
