#include "EffectPermutation.hpp"
#include "../entity/Entity.hpp"
#include "../fight/Fight.hpp"

void EffectPermutation::apply(Fight* fight) {
	auto start = caster->cell;
	auto end = target->cell;
	if (start == nullptr or end == nullptr) {
		return;
	}
	start->setEntity(target);
	end->setEntity(caster);
}
