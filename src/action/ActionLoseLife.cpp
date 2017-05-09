#include "ActionLoseLife.hpp"

ActionLoseLife::ActionLoseLife(Entity* target, int life) {
	this->target = target->id;
	this->life = life;
}

Json ActionLoseLife::json() const {
	return {(int) ActionType::LOST_LIFE, target, life};
}
