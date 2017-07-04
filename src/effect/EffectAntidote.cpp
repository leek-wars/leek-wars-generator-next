#include "EffectAntidote.hpp"
#include "../entity/Entity.hpp"

void EffectAntidote::apply(Fight*) {
	target->clear_poisons();
}
