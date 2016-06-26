#ifndef ACTION_ADD_EFFECT
#define ACTION_ADD_EFFECT

#include "Action.hpp"
class Entity;
enum class AttackType;
enum class EffectType;

class ActionAddEffect : public Action {
public:
	int attack_id;
	int effect_id;
	int caster;
	int target;
	EffectType effect_type;
	int value;
	int turns;

	ActionAddEffect(AttackType type, int attackID, Entity* caster, Entity* target, EffectType effect_type, int effect_id, int value, int turns);
	virtual ~ActionAddEffect();

	virtual Json json() const override;
};

#endif
