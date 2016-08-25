/*
 * Effect.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: pierre
 */

#include "../fight/Fight.hpp"
#include "../effect/Effect.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionAddEffect.hpp"

#include "EffectDamage.hpp"
#include "EffectRelativeShield.hpp"

Effect::Effect() {
	native = true;
}

Effect::~Effect() {}

void Effect::apply(Fight* fight) {
	// nothing by default
}

void Effect::applyStartTurn(Fight* fight) {
	// nothing by default
}

int Effect::getEffectValue() const {
	return 0;
}

void Effect::createEffect(Fight* fight, EffectType type, int turns, double power, double value1, double value2, bool critical, Entity* target, Entity* caster, AttackType attack_type, int attack_id, double jet) {

	cout << "create effect " << endl;

	// Create the effect
	Effect* effect = Effect::construct(type);
	if (effect == nullptr) {
		return;
	}
	effect->type = type;
	effect->turns = turns;
	effect->power = power;
	effect->value1 = value1;
	effect->value2 = value2;
	effect->critical = critical;
	effect->critical_power = critical ? CRITICAL_POWER : 1.0;
	effect->caster = caster;
	effect->target = target;
	effect->attackType = attack_type;
	effect->attackID = attack_id;
	effect->jet = jet;

	// Add effect to the target and the caster
	if (effect->turns > 0) {

		// TODO : create a isStackable method
		bool stackable = type == EffectType::POISON || type == EffectType::SHACKLE_MP
				|| type == EffectType::SHACKLE_TP || type == EffectType::SHACKLE_STRENGTH
				|| type == EffectType::SHACKLE_MAGIC;

		if (!stackable) {
			vector<ls::LSValue*> effects = target->getEffects();

			for (unsigned i = 0; i < effects.size(); ++i) {
				Effect* e = (Effect*) effects[i];
				if (e->attackID == attack_id) {
					target->removeEffect(e);
					break;
				}
			}
		}

		target->addEffect(effect);
		caster->addLaunchedEffect(effect);
	}

	// Compute the effect
	effect->apply(fight);

	fight->actions.add(new ActionAddEffect(attack_type, attack_id, caster,
		target, type, fight->actions.getEffectId(), effect->getEffectValue(),
		effect->turns));
}

Effect* Effect::construct(EffectType type) {
	switch (type) {
		case EffectType::DAMAGE: return new EffectDamage();
		//case EffectType::HEAL: return new EffectHeal();
		case EffectType::RELATIVE_SHIELD: return new EffectRelativeShield();
		default:
			return nullptr;
	}
}
