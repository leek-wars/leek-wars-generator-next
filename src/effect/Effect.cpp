#include "../fight/Fight.hpp"
#include "../effect/Effect.hpp"
#include "../entity/Entity.hpp"
#include "../action/ActionAddEffect.hpp"
#include "../util/Util.hpp"
#include "EffectDamage.hpp"
#include "EffectHeal.hpp"
#include "EffectRelativeShield.hpp"
#include "EffectAbsoluteShield.hpp"
#include "EffectPoison.hpp"
#include "EffectAntidote.hpp"
#include "EffectShackleMP.hpp"
#include "EffectShackleTP.hpp"
#include "EffectShackleMagic.hpp"
#include "EffectShackleStrength.hpp"
#include "EffectKill.hpp"
#include "EffectBuffStrength.hpp"
#include "EffectBuffAgility.hpp"
#include "EffectBuffTP.hpp"
#include "EffectBuffMP.hpp"
#include "EffectDebuff.hpp"
#include "EffectTeleport.hpp"
#include "EffectPermutation.hpp"

Effect::Effect() {
	native = true;
}

Effect::~Effect() {}

void Effect::apply(Fight*) {
	// nothing by default
}

void Effect::applyStartTurn(Fight*) {
	// nothing by default
}

int Effect::getEffectValue() const {
	return 0;
}

bool Effect::stackable() const {
	return false;
}

void Effect::createEffect(Fight* fight, EffectType type, int turns, double power, double value1, double value2, bool critical, Entity* target, Entity* caster, AttackType attack_type, int attack_id, double jet) {

	// Create the effect
	auto effect = Effect::construct(type);
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
		if (!effect->stackable()) {
			auto effects = target->getEffects();
			for (unsigned i = 0; i < effects.size(); ++i) {
				auto e = (Effect*) effects[i];
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

	fight->actions.add(new ActionAddEffect(attack_type, attack_id, caster, target, type, fight->actions.getEffectId(), effect->getEffectValue(), effect->turns));
}

Effect* Effect::construct(EffectType type) {
	switch (type) {
		case EffectType::DAMAGE: return new EffectDamage();
		case EffectType::HEAL: return new EffectHeal();
		case EffectType::POISON: return new EffectPoison();
		case EffectType::RELATIVE_SHIELD: return new EffectRelativeShield();
		case EffectType::ABSOLUTE_SHIELD: return new EffectAbsoluteShield();
		case EffectType::ANTIDOTE: return new EffectAntidote();
		case EffectType::SHACKLE_MP: return new EffectShackleMP();
		case EffectType::SHACKLE_TP: return new EffectShackleTP();
		case EffectType::SHACKLE_MAGIC: return new EffectShackleMagic();
		case EffectType::SHACKLE_STRENGTH: return new EffectShackleStrength();
		case EffectType::KILL: return new EffectKill();
		case EffectType::BUFF_STRENGTH: return new EffectBuffStrength();
		case EffectType::BUFF_AGILITY: return new EffectBuffAgility();
		case EffectType::BUFF_TP: return new EffectBuffTP();
		case EffectType::BUFF_MP: return new EffectBuffMP();
		case EffectType::DEBUFF: return new EffectDebuff();
		case EffectType::TELEPORT: return new EffectTeleport();
		case EffectType::PERMUTATION: return new EffectPermutation();
		default:
			LOG_E << "No such effect!" << std::endl;
			assert(false or "No such effect!");
			return nullptr;
	}
}
