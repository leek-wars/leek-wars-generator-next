#include "EffectRelativeShield.hpp"
#include "../entity/Entity.hpp"

EffectRelativeShield::EffectRelativeShield() {}

EffectRelativeShield::~EffectRelativeShield() {}

void EffectRelativeShield::apply(Fight*) {

	int shield = (int) round((value1 + jet * value2) * (1 + (double) caster->getResistance() / 100) * power * critical_power);

	characs.set(Characteristic::RELATIVE_SHIELD, shield);
	target->updateBonusCharacteristics(Characteristic::RELATIVE_SHIELD);
}

int EffectRelativeShield::getEffectValue() const {
	return characs.get(Characteristic::RELATIVE_SHIELD);
}
