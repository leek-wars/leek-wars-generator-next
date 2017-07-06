#ifndef EFFECT_SHACKLE_TP_HPP
#define EFFECT_SHACKLE_TP_HPP

#include "Effect.hpp"

class EffectShackleTP: public Effect {
public:
	int shackle;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
