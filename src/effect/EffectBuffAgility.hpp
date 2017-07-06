#ifndef EFFECT_BUFF_AGILITY_HPP
#define EFFECT_BUFF_AGILITY_HPP

#include "Effect.hpp"

class EffectBuffAgility: public Effect {
public:
	int buff;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
