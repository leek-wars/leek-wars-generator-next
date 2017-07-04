#include <math.h>
#include "EffectPoison.hpp"
#include "../entity/Entity.hpp"
#include "../fight/Fight.hpp"
#include "../action/ActionLoseLife.hpp"

void EffectPoison::apply(Fight*) {
	poison = (int) round(((value1 + jet * value2)) * (1 + (double) fmax(0, caster->getMagic()) / 100) * power * critical_power);
}

void EffectPoison::applyStartTurn(Fight* fight) {
	int damage = poison;
	if (target->getLife() < damage) {
		damage = target->getLife();
	}
	fight->actions.add(new ActionLoseLife(target, damage));
	target->removeLife(damage, caster);
	// TODO Manage statistics
	// fight.statistics.addDamagePoison(damages);
}

int EffectPoison::getEffectValue() const {
	return poison;
}

bool EffectPoison::stackable() const {
	return true;
}
