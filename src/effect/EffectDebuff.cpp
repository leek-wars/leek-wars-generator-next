#include "EffectDebuff.hpp"
#include "../entity/Entity.hpp"
#include "../fight/Fight.hpp"

void EffectDebuff::apply(Fight*) {
	target->clear_effects();
}
