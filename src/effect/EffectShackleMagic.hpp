#ifndef EFFECT_SHACKLE_MAGIC_HPP
#define EFFECT_SHACKLE_MAGIC_HPP

#include "Effect.hpp"

class EffectShackleMagic: public Effect {
public:
	int shackle;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
	virtual bool stackable() const override;
};

#endif
