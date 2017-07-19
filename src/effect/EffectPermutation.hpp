#ifndef EFFECT_PERMUTATION_HPP
#define EFFECT_PERMUTATION_HPP

#include "Effect.hpp"

class EffectPermutation : public Effect {
public:
	virtual void apply(Fight* fight) override;
};

#endif
