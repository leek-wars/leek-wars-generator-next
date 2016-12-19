#include "ActionStartFight.hpp"
#include "../entity/Entity.hpp"

ActionStartFight::ActionStartFight() {}

Json ActionStartFight::json() const {
	return {(int) ActionType::START_FIGHT};
}
