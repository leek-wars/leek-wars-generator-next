#include <math.h>
#include "EffectDamage.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionLoseLife.hpp"
#include "../action/ActionHeal.hpp"
#include "../fight/Fight.hpp"

EffectDamage::EffectDamage() {}

EffectDamage::~EffectDamage() {}

void EffectDamage::apply(Fight* fight) {

	// Base damages
	double d = (value1 + jet * value2) * (1 + max(0, caster->getStrength()) / 100.0) * power * critical_power;

	// Return damage
	if (target != caster) {
		return_damage = (int) round(d * target->getDamageReturn() / 100.0);
	}

	// Shields
	d -= d * (target->getRelativeShield() / 100.0) + target->getAbsoluteShield();
	d = max(0.0, d);

	damage = (int) round(d);

	if (target->getLife() < damage) {
		damage = target->getLife();
	}

	// Life steal
	if (target != caster) {
		life_steal = (int) round(damage * caster->getWisdom() / 1000.0);
	}

	// One shoot
	if (target->getTotalLife() == damage && caster != target) {
		// TODO
		// fight.getTrophyManager().roxxor(caster);
	}

	fight->actions.add(new ActionLoseLife(target, damage));
	target->removeLife(damage, caster);

	// Life steal
	if (life_steal > 0) {

		if (caster->getLife() + life_steal > caster->getTotalLife()) {
			life_steal = caster->getTotalLife() - caster->getLife();
		}
		if (life_steal > 0) {
			fight->actions.add(new ActionHeal(caster, life_steal));
			caster->addLife(life_steal);
		}
	}

	// Return damage (no return damage is the target is dead during the attack)
	if (return_damage > 0 and target->isAlive()) {
		if (caster->getLife() < return_damage) {
			return_damage = caster->getLife();
		}
		if (return_damage > 0) {
			fight->actions.add(new ActionLoseLife(caster, return_damage));
			caster->removeLife(return_damage, target);
		}
	}
}

int EffectDamage::getEffectValue() const {
	return damage;
}
