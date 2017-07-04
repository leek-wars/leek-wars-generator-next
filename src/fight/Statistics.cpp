#include "Statistics.hpp"
#include "../entity/Entity.hpp"

void Statistics::add_damage(Entity* attacker, int damage, Entity*) {
	damages.insert({attacker->id, damage});
}
