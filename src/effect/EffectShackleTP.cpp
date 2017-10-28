#include "EffectShackleTP.hpp"
#include "../entity/Entity.hpp"

void EffectShackleTP::apply(Fight*) {

	// Base shackle : base × (1 + magic / 100)
	double s = (value1 + jet * value2) * (1.0 + std::max(0, caster->getMagic() - target->getScience()) / 100.0) * power * critical_power;
	shackle = (int) round(s);

	characs.set(Characteristic::TP, -shackle);
	target->updateBonusCharacteristics(Characteristic::TP);
}

int EffectShackleTP::getEffectValue() const {
	return shackle;
}

bool EffectShackleTP::stackable() const {
	return true;
}
