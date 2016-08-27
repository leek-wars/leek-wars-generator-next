#include "ActionEndTurn.hpp"
#include "../entity/Entity.hpp"

ActionEndTurn::ActionEndTurn(Entity* target) {

	this->target = target->id;
	this->tp = target->getTP();
	this->mp = target->getMP();
	this->strength = target->getStrength();
	this->magic = target->getMagic();
}

Json ActionEndTurn::json() const {

	return {(int) ActionType::END_TURN, target, tp, mp, strength, magic};
}
