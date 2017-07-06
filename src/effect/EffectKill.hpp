#ifndef EFFECT_KILL_HPP
#define EFFECT_KILL_HPP

#include "Effect.hpp"

class EffectKill : public Effect {

	int damage = 0;

public:

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
