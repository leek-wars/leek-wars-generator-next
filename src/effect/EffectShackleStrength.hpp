#ifndef EFFECT_SHACKLE_STRENGTH_HPP
#define EFFECT_SHACKLE_STRENGTH_HPP

#include "Effect.hpp"

class EffectShackleStrength: public Effect {
public:
	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
