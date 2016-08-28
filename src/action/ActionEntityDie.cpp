#include "ActionEntityDie.hpp"
#include "../entity/Entity.hpp"

ActionEntityDie::ActionEntityDie(Entity* leek, Entity* killer) {
	this->id = leek->id;
	this->killer = killer != nullptr ? killer->id : -1;
}

Json ActionEntityDie::json() const {
	return {(int) ActionType::PLAYER_DEAD, id, killer};
}

