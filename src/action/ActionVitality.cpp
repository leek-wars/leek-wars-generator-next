#include "ActionVitality.hpp"

ActionVitality::ActionVitality(Entity* target, int life)
	: target(target->id), life(life) {}

Json ActionVitality::json() const {
	return {(int) ActionType::VITALITY, target, life};
}
