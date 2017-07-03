#include "ActionLoseMP.hpp"
#include "../entity/Entity.hpp"

ActionLoseMP::ActionLoseMP(Entity* target, int mp)
	: target(target->id), mp(mp) {}

Json ActionLoseMP::json() const {
	return {(int) ActionType::LOST_MP, target, mp};
}
