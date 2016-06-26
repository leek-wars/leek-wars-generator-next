#include "ActionLoseTP.hpp"

#include "../entity/Entity.hpp"

ActionLoseTP::ActionLoseTP(Entity* target, int tp)
	: target(target->id), tp(tp) {}

Json ActionLoseTP::json() const {
	return {(int) ActionType::LOST_TP, target, tp};
}
