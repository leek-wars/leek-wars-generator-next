#include "ActionAddEffect.hpp"
#include "../effect/Attack.hpp"
#include "../entity/Entity.hpp"

ActionAddEffect::ActionAddEffect(AttackType type, int attack_id, Entity* caster, Entity* target, EffectType effect_type, int effect_id, int value, int turns) {

	if (type == AttackType::CHIP) {
		this->type = ActionType::ADD_CHIP_EFFECT;
	} else if (type == AttackType::WEAPON) {
		this->type = ActionType::ADD_WEAPON_EFFECT;
	}
	this->attack_id = attack_id;
	this->effect_id = effect_id;
	this->caster = caster->id;
	this->target = target->id;
	this->effect_type = effect_type;
	this->value = value;
	this->turns = turns;
}

ActionAddEffect::~ActionAddEffect() {}

Json ActionAddEffect::json() const {
	return {(int) type, attack_id, effect_id, caster, target, (int) effect_type, value, turns};
}
