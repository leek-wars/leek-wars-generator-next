#ifndef EFFECT_DEBUFF_HPP
#define EFFECT_DEBUFF_HPP

#include "Effect.hpp"

class EffectDebuff : public Effect {
public:
	virtual void apply(Fight* fight) override;
};

#endif
