#ifndef EFFECT_VITALITY_HPP
#define EFFECT_VITALITY_HPP

#include "Effect.hpp"

class EffectVitality : public Effect {

	int vitality = 0;

public:

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
