#include "ActionKill.hpp"
#include "../entity/Entity.hpp"

ActionKill::ActionKill(Entity* caster, Entity* target) {
	this->caster = caster->id;
	this->target = target->id;
}

Json ActionKill::json() const {
	return {(int) ActionType::KILL, caster, target};
}
