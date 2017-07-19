#include <math.h>
#include "EffectVitality.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionVitality.hpp"
#include "../fight/Fight.hpp"

void EffectVitality::apply(Fight* fight) {

	vitality = (int) round((value1 + jet * value2) * (1 + caster->getWisdom() / 100.0) * power * critical_power);

	fight->actions.add(new ActionVitality(target, vitality));
	target->addMaximumLife(vitality);
	target->addLife(vitality);
}

int EffectVitality::getEffectValue() const {
	return vitality;
}
