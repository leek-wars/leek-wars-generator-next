#ifndef EFFECT_HEAL_HPP
#define EFFECT_HEAL_HPP

#include "Effect.hpp"

class EffectHeal : public Effect {

	int heal = 0;

public:

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
