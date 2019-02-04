#include "ActionLoseLife.hpp"

ActionLoseLife::ActionLoseLife(Entity* target, int life, int erosion) {
	this->target = target->id;
	this->life = life;
	this->erosion = erosion;
}

Json ActionLoseLife::json() const {
	return {(int) ActionType::LOST_LIFE, target, life, erosion};
}
