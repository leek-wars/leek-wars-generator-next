#ifndef EFFECT_POISON_HPP
#define EFFECT_POISON_HPP

#include "Effect.hpp"

class EffectPoison : public Effect {

	int poison = 0;

public:

	virtual void apply(Fight* fight) override;
	virtual void applyStartTurn(Fight* fight) override;
	virtual int getEffectValue() const override;
	virtual bool stackable() const override;
};

#endif
