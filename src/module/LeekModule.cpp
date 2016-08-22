#include "LeekModule.hpp"
#include "../entity/Leek.hpp"
#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* LeekModule::leek_clazz;
const LeekType* const LeekModule::type = new LeekType();
const ls::Type LeekModule::type_ptr(LeekModule::type, ls::Nature::POINTER);

LeekModule::LeekModule() : Module("Leek") {

	method("getFarmerID", LeekModule::type_ptr, Type::INTEGER_P, {LeekModule::type_ptr}, (void*) &leek_getFarmerID);
	method("getFarmerName", LeekModule::type_ptr, Type::STRING, {LeekModule::type_ptr}, (void*) &leek_getFarmerName);

	// V1 methods
	static_method("_getAIID", {
		{Type::INTEGER, {}, (void*) &leek__getAIID},
		{Type::POINTER, {Type::POINTER}, (void*) &leek__getAIIDEntity},
	});
	static_method("_getAIName", {
		{Type::STRING, {}, (void*) &leek__getAIName},
		{Type::POINTER, {Type::POINTER}, (void*) &leek__getAINameEntity},
	});
	static_method("_getFarmerID", {
		{Type::INTEGER, {}, (void*) &leek__getFarmerID},
		{Type::POINTER, {Type::POINTER}, (void*) &leek__getFarmerIDEntity},
	});
	static_method("_getFarmerName", {
		{Type::STRING, {}, (void*) &leek__getFarmerName},
		{Type::POINTER, {Type::POINTER}, (void*) &leek__getFarmerNameEntity},
	});
}

LeekModule::~LeekModule() {}

const ls::LSNumber* leek_getFarmerID(Leek* leek) {
	return (ls::LSNumber*) leek->values["farmerID"];
}

const ls::LSString* leek_getFarmerName(Leek* leek) {
	return (ls::LSString*) leek->values["farmerName"];
}


/*
 * V1 methods
 */
inline Entity* leek__getEntity(const ls::LSValue* entity) {

	if (dynamic_cast<const ls::LSNull*>(entity)) {
		return Simulator::entity;
	}
	if (const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(entity)) {
		return Simulator::fight->getEntity(n->value);
	}
	return nullptr;
}

int leek__getAIID() {
	return Simulator::entity->ai->id;
}
ls::LSValue* leek__getAIIDEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->ai->id);
}

ls::LSString* leek__getAIName() {
	return new ls::LSString(Simulator::entity->ai->name);
}
ls::LSValue* leek__getAINameEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->ai->name);
}

int leek__getFarmerID() {
	// TODO
	return 0;
}
ls::LSValue* leek__getFarmerIDEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSString* leek__getFarmerName() {
	// TODO
	return new ls::LSString(Simulator::entity->farmer_name);
}
ls::LSValue* leek__getFarmerNameEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->farmer_name);
}
