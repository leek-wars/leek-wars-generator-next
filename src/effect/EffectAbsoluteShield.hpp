#ifndef SRC_EFFECT_EFFECTABSOLUTESHIELD_HPP_
#define SRC_EFFECT_EFFECTABSOLUTESHIELD_HPP_

#include "Effect.hpp"

class EffectAbsoluteShield : public Effect {
public:

	virtual void apply(Fight* fight);

	virtual int getEffectValue();
};

#endif
