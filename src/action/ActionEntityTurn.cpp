#include "ActionEntityTurn.hpp"
#include "../entity/Entity.hpp"

ActionEntityTurn::ActionEntityTurn(Entity* entity) {
	this->id = entity->id;
	this->tp = entity->getTP();
	this->mp = entity->getMP();
}

Json ActionEntityTurn::json() const {
	return {(int) ActionType::ENTITY_TURN, id, tp, mp};
}
