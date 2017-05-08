#ifndef SRC_EFFECT_EFFECTDAMAGE_HPP_
#define SRC_EFFECT_EFFECTDAMAGE_HPP_

#include "Effect.hpp"

class EffectDamage : public Effect {

	int damage = 0;
	int return_damage = 0;
	int life_steal = 0;

public:

	EffectDamage();
	virtual ~EffectDamage();

	virtual void apply(Fight* fight) override;

	virtual int getEffectValue() const override;
};

#endif
