#include "EffectBuffTP.hpp"
#include "../entity/Entity.hpp"

void EffectBuffTP::apply(Fight*) {

	buff = (int) round((value1 + value2 * jet) * (1 + (double) caster->getScience() / 100) * power * critical_power);

	characs.set(Characteristic::TP, buff);
	target->updateBonusCharacteristics(Characteristic::TP);
}

int EffectBuffTP::getEffectValue() const {
	return buff;
}
