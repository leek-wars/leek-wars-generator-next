/*
 * FightModule.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: pierre
 */

#include "FightModule.hpp"
#include "../Simulator.hpp"
#include "../entity/Entity.hpp"
#include "../fight/Fight.hpp"

jit_value_t Fight_MAX_TURNS(jit_function_t F) { return LS_CREATE_INTEGER(F, 64); }

FightModule::FightModule() : Module("Fight") {

	static_field("MAX_TURNS", Type::INTEGER, (void*) &Fight_MAX_TURNS);

	static_method("getTurn", Type::INTEGER, {}, (void*) &fight_getTurn);
	static_method("getEntity", EntityModule::type_ptr, {}, (void*) &fight_getEntity);

	static_method("getType", Type::INTEGER, {}, (void*) &fight_getType);
	static_method("getContext", Type::INTEGER, {}, (void*) &fight_getContext);
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
