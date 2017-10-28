#include "EffectShackleStrength.hpp"
#include "../entity/Entity.hpp"

void EffectShackleStrength::apply(Fight*) {

	// Base shackle : base × (1 + magic / 100)
	double s = (value1 + jet * value2) * (1.0 + std::max(0, caster->getMagic() - target->getScience()) / 100.0) * power * critical_power;
	shackle = (int) round(s);

	characs.set(Characteristic::STRENGTH, -shackle);
	target->updateBonusCharacteristics(Characteristic::STRENGTH);
}

int EffectShackleStrength::getEffectValue() const {
	return shackle;
}

bool EffectShackleStrength::stackable() const {
	return true;
}
