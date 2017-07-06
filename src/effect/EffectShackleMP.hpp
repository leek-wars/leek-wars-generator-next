#ifndef EFFECT_SHACKLE_MP_HPP
#define EFFECT_SHACKLE_MP_HPP

#include "Effect.hpp"

class EffectShackleMP: public Effect {
public:
	int shackle;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
