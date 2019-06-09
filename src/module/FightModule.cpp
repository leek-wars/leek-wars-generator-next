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

FightModule::FightModule(ls::VM* vm) : Module(vm, "Fight") {

	static_field("MAX_TURNS", ls::Type::integer, [](ls::Compiler& c) { return c.new_integer(64); });

	method("getTurn", {
		{ls::Type::integer, {}, (void*) &fight_getTurn}
	});
	method("getEntity", {
		{EntityModule::type, {}, (void*) &fight_getEntity}
	});
	method("getType", {{ls::Type::integer, {}, (void*) &fight_getType}});
	method("getContext", {{ls::Type::integer, {}, (void*) &fight_getContext}});

	// V1
	method("getLeek", {{ls::Type::integer, {}, (void*) &fight__getEntity}});
}

FightModule::~FightModule() {}

int fight_getTurn() {
	return Simulator::fight->turn();
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

int fight__getEntity() {
	return Simulator::entity->id;
}