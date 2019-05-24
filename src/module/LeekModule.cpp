#include "LeekModule.hpp"
#include "../entity/Leek.hpp"
#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../fight/Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* LeekModule::leek_clazz;
const std::shared_ptr<LeekType> LeekModule::type = std::make_shared<LeekType>();
const ls::Type LeekModule::type_ptr(LeekModule::type);

LeekModule::LeekModule() : Module("Leek") {

	method("getFarmerID", {
		{ls::Type::integer(), {LeekModule::type_ptr}, (void*) &leek_getFarmerID, ls::Method::NATIVE}
	});
	method("getFarmerName", {
		{ls::Type::string(), {LeekModule::type_ptr}, (void*) &leek_getFarmerName, ls::Method::NATIVE}
	});

	// V1 methods
	method("getAIID", ls::Method::Static, {
		{ls::Type::integer(), {}, (void*) &leek__getAIID, ls::Method::NATIVE},
		{ls::Type::any(), {ls::Type::any()}, (void*) &leek__getAIIDEntity, ls::Method::NATIVE},
	});
	method("getAIName", ls::Method::Static, {
		{ls::Type::string(), {}, (void*) &leek__getAIName, ls::Method::NATIVE},
		{ls::Type::any(), {ls::Type::any()}, (void*) &leek__getAINameEntity, ls::Method::NATIVE},
	});
	method("getFarmerID", ls::Method::Static, {
		{ls::Type::integer(), {}, (void*) &leek__getFarmerID, ls::Method::NATIVE},
		{ls::Type::any(), {ls::Type::any()}, (void*) &leek__getFarmerIDEntity, ls::Method::NATIVE},
	});
	method("getFarmerName", ls::Method::Static, {
		{ls::Type::string(), {}, (void*) &leek__getFarmerName, ls::Method::NATIVE},
		{ls::Type::any(), {ls::Type::any()}, (void*) &leek__getFarmerNameEntity, ls::Method::NATIVE},
	});
}

LeekModule::~LeekModule() {}

int leek_getFarmerID(Leek* leek) {
	return leek->farmer;
}

const ls::LSString* leek_getFarmerName(Leek* leek) {
	return (ls::LSString*) leek->getField("farmerName");
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
