#include "EffectAntidote.hpp"
#include "../entity/Entity.hpp"

void EffectAntidote::apply(Fight* fight) {
	target->clear_poisons();
}
