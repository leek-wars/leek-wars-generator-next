#ifndef EFFECT_BUFF_TP_HPP
#define EFFECT_BUFF_TP_HPP

#include "Effect.hpp"

class EffectBuffTP: public Effect {
public:
	int buff;

	virtual void apply(Fight* fight) override;
	virtual int getEffectValue() const override;
};

#endif
