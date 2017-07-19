#include "EffectBuffMP.hpp"
#include "../entity/Entity.hpp"

void EffectBuffMP::apply(Fight*) {

	buff = (int) round((value1 + value2 * jet) * (1 + (double) caster->getScience() / 100) * power * critical_power);

	characs.set(Characteristic::MP, buff);
	target->updateBonusCharacteristics(Characteristic::MP);
}

int EffectBuffMP::getEffectValue() const {
	return buff;
}
