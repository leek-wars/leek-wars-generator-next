#ifndef EFFECT_SHACKLE_STRENGTH_HPP
#define EFFECT_SHACKLE_STRENGTH_HPP

#include "Effect.hpp"

class EffectShackleStrength: public Effect {
public:
	int shackle;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
	virtual bool stackable() const override;
};

#endif
