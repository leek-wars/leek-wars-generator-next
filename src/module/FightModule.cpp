#include "FightModule.hpp"
#include "../fight/Simulator.hpp"
#include "../entity/Entity.hpp"
#include "../fight/Fight.hpp"

/*
 * class Fight {
 * 		enum Type {
 * 			SOLO, FARMER, TEAM, BR
 * 		}
 * 		enum Context {
 * 			TEST, GARDEN, CHALLENGE
 * 		}
 * }
 *
 * Fight.Type.SOLO
 * let ctx = Fight.Context.GARDEN
 */

jit_value_t Fight_MAX_TURNS(jit_function_t F) { return LS_CREATE_INTEGER(F, 64); }

FightModule::FightModule() : Module("Fight") {

	static_field("MAX_TURNS", ls::Type::INTEGER, (void*) &Fight_MAX_TURNS);

	static_method("getTurn", ls::Type::INTEGER, {}, (void*) &fight_getTurn);
	static_method("getEntity", {
		{EntityModule::type_ptr, {}, (void*) &fight_getEntity, ls::Method::NATIVE}
	});

	static_method("getType", ls::Type::INTEGER, {}, (void*) &fight_getType);
	static_method("getContext", ls::Type::INTEGER, {}, (void*) &fight_getContext);
}

FightModule::~FightModule() {}

int fight_getTurn() {
	return Simulator::fight->turn;
}

Entity* fight_getEntity() {
	return Simulator::entity;
}

int fight_getType() {
	return Simulator::fight->type;
}

int fight_getContext() {
	return Simulator::fight->context;
}
