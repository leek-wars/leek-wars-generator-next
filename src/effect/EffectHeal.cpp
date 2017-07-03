#include <math.h>
#include "EffectHeal.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionHeal.hpp"
#include "../fight/Fight.hpp"

void EffectHeal::apply(Fight* fight) {

	heal = (int) round((value1 + jet * value2) * (1 + (double) caster->getWisdom() / 100) * power * critical_power);

	if (turns == 0) {
		if (target->getLife() + heal > target->getTotalLife()) {
			heal = target->getTotalLife() - target->getLife();
		}
		fight->actions.add(new ActionHeal(target, heal));
		target->addLife(heal);
	}
}

int EffectHeal::getEffectValue() const {
	return heal;
}
