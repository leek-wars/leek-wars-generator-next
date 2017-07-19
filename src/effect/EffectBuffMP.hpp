#ifndef EFFECT_BUFF_MP_HPP
#define EFFECT_BUFF_MP_HPP

#include "Effect.hpp"

class EffectBuffMP: public Effect {
public:
	int buff;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
