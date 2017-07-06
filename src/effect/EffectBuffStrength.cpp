#include "EffectBuffStrength.hpp"
#include "../entity/Entity.hpp"

void EffectBuffStrength::apply(Fight*) {

	buff = (int) round((value1 + value2 * jet) * (1 + (double) caster->getScience() / 100) * power * critical_power);

	characs.set(Characteristic::STRENGTH, buff);
	target->updateBonusCharacteristics(Characteristic::STRENGTH);
}

int EffectBuffStrength::getEffectValue() const {
	return buff;
}
