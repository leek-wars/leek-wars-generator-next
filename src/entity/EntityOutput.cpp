#include "EntityOutput.hpp"
#include "Entity.hpp"
#include "../fight/Fight.hpp"
#include "../action/Actions.hpp"
#include "../action/Action.hpp"

void EntityOutput::end() {
	entity->fight->actions.add_entity_log(entity, oss.str());
	oss.str("");
}