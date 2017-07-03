#include "ActionSay.hpp"
#include "../entity/Entity.hpp"

ActionSay::ActionSay(Entity* entity, std::string& message)
	: entity(entity->id), message(message) {}

Json ActionSay::json() const {
	return {(int) ActionType::SAY, entity, message};

}
