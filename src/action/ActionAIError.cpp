#include "ActionAIError.hpp"
#include "../entity/Entity.hpp"

ActionAIError::ActionAIError(Entity* target) : id(target->id) {}

Json ActionAIError::json() const {
	return {(int) ActionType::AI_ERROR, id};
}
