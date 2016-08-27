#include "ActionHeal.hpp"
#include "../entity/Entity.hpp"

ActionHeal::ActionHeal(Entity* target, int life) {
	this->target = target->id;
	this->life = life;
}

Json ActionHeal::json() const {
	return {(int) ActionType::HEAL, target, life};
}
