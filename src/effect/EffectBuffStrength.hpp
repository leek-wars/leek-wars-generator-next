#ifndef EFFECT_BUFF_STRENGTH_HPP
#define EFFECT_BUFF_STRENGTH_HPP

#include "Effect.hpp"

class EffectBuffStrength: public Effect {
public:
	int buff;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
