#ifndef EFFECT_SHACKLE_MAGIC_HPP
#define EFFECT_SHACKLE_MAGIC_HPP

#include "Effect.hpp"

class EffectShackleMagic: public Effect {
public:
	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
