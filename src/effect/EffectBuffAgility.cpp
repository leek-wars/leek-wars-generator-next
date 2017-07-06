#include "EffectBuffAgility.hpp"
#include "../entity/Entity.hpp"

void EffectBuffAgility::apply(Fight*) {

	buff = (int) round((value1 + value2 * jet) * (1 + (double) caster->getScience() / 100) * power * critical_power);

	characs.set(Characteristic::AGILITY, buff);
	target->updateBonusCharacteristics(Characteristic::AGILITY);
}

int EffectBuffAgility::getEffectValue() const {
	return buff;
}
