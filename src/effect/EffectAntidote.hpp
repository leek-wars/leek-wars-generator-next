#ifndef EFFECT_ANTIDOTE_HPP
#define EFFECT_ANTIDOTE_HPP

#include "Effect.hpp"

class EffectAntidote : public Effect {
public:
	void apply(Fight* fight) override;
};

#endif
