/*
 * EffectRelativeShield.cpp
 *
 *  Created on: May 17, 2016
 *      Author: pierre
 */

#include "EffectRelativeShield.hpp"
#include "../entity/Entity.hpp"

EffectRelativeShield::EffectRelativeShield() {
	// TODO Auto-generated constructor stub

}

EffectRelativeShield::~EffectRelativeShield() {
	// TODO Auto-generated destructor stub
}

void EffectRelativeShield::apply(Fight*) {

	int shield = (int) round((value1 + jet * value2) * (1 + (double) caster->getResistance() / 100) * power * critical_power);

	characs.set(Characteristic::RELATIVE_SHIELD, shield);
	target->updateBonusCharacteristics(Characteristic::RELATIVE_SHIELD);
}

int EffectRelativeShield::getEffectValue() const {
	return characs.get(Characteristic::RELATIVE_SHIELD);
}
