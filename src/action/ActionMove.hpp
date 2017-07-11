#ifndef ACTION_MOVE_HPP
#define ACTION_MOVE_HPP

#include <vector>
#include "Action.hpp"
class Cell;
#include "../entity/Entity.hpp"

class ActionMove : public Action {
public:
	int entity;
	std::vector<int> path;
	int end;

	ActionMove(Entity* entity, std::vector<const Cell*> path);

	virtual Json json() const override;
};

#endif
