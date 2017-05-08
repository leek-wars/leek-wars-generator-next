#include "EffectAbsoluteShield.hpp"
#include "../entity/Entity.hpp"

void EffectAbsoluteShield::apply(Fight*) {

	int value = (int) round((value1 + jet * value2) * (1 + caster->getResistance() / 100.0) * power * critical_power);

	characs.set(Characteristic::ABSOLUTE_SHIELD, value);
	target->updateBonusCharacteristics(Characteristic::ABSOLUTE_SHIELD);
}

int EffectAbsoluteShield::getEffectValue() {
	return characs.get(Characteristic::ABSOLUTE_SHIELD);
}
