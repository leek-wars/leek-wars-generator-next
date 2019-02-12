#include "Simulator.hpp"

Fight* Simulator::fight;
Entity* Simulator::entity;

/*
 * Internal function to get a entity from the function argument
 * Null -> my entity
 * Number -> an entity id, try to get it
 */
Entity* Simulator::getEntity(const ls::LSValue* entity) {
	if (dynamic_cast<const ls::LSNull*>(entity)) {
		return Simulator::entity;
	}
	if (const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(entity)) {
		return Simulator::fight->getEntity(n->value);
	}
	return nullptr;
}