#include "EffectKill.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionLoseLife.hpp"
#include "../fight/Fight.hpp"

void EffectKill::apply(Fight* fight) {
	damage = target->getLife();
	fight->actions.add(new ActionLoseLife(target, damage));
	target->removeLife(damage, caster);
}

int EffectKill::getEffectValue() const {
	return damage;
}
