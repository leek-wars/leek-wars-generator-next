#include "WeaponModule.hpp"
#include "../util/Util.hpp"
#include "../fight/Simulator.hpp"

const ls::LSClass* WeaponModule::weapon_clazz;
const std::shared_ptr<WeaponType> WeaponModule::raw_type = std::make_shared<WeaponType>();
const ls::Type WeaponModule::type(raw_type, true);
const ls::Type WeaponModule::const_type(raw_type, true, false, true);
const ls::Type WeaponModule::array_type = ls::Type::array(WeaponModule::type);

WeaponModule::WeaponModule(const FightManager& manager) : Module("Weapon") {

	for (const auto& w : manager.weapons) {
		static_field(Util::toupper(w.second->name), ls::Type::integer(), [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
	}

	field("id", ls::Type::number());
	field("cost", ls::Type::number());
	field("name", ls::Type::string());

	// V1
	method("getWeaponCost", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponCost, ls::Method::NATIVE},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponCostWeapon, ls::Method::NATIVE},
	});
	method("getWeaponEffects", {
		{ls::Type::any(), {}, (void*) &weapon__getWeaponEffects, ls::Method::NATIVE},
		{ls::Type::any(), {ls::Type::any()}, (void*) &weapon__getWeaponEffectsWeapon, ls::Method::NATIVE},
	});
	method("getWeaponMinRange", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponMinRange, ls::Method::NATIVE},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponMinRangeWeapon, ls::Method::NATIVE},
	});
	method("getWeaponMaxRange", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponMaxRange, ls::Method::NATIVE},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponMaxRangeWeapon, ls::Method::NATIVE},
	});
}

WeaponModule::~WeaponModule() {}

/*
 * V1 methods
 */
bool weapon__canUseWeapon(const ls::LSValue* entity) {

}
bool weapon__canUseWeaponWeapon(const ls::LSValue* weapon, const ls::LSValue* entity) {

}

bool weapon__canUseWeaponOnCell(const ls::LSValue* cell) {

}
bool weapon__canUseWeaponOnCellWeapon(const ls::LSValue* weapon, const ls::LSValue* cell) {

}

/*
 * Returns null or integer
 */
ls::LSValue* weapon__getWeaponArea(const ls::LSValue* weapon) {

}
/*
 * Always returns an integer
 */
int weapon__getWeaponCost() {
	return Simulator::entity->weapon->cost;
}
int weapon__getWeaponCostWeapon(const ls::LSValue* weapon) {
	if (auto number = dynamic_cast<const ls::LSNumber*>(weapon)) {
		auto i = Simulator::fight->manager->weapons.find(number->value);
		if (i != Simulator::fight->manager->weapons.end()) {
			return i->second->cost;
		}
	}
	return -1;
}

/*
 * Returns null when arguments are invalid, an int array otherwise
 */
ls::LSValue* weapon__getWeaponEffectiveArea(const ls::LSValue* cell) {

}
ls::LSValue* weapon__getWeaponEffectiveAreaWeapon(const ls::LSValue* weapon, const ls::LSValue* cell) {

}
ls::LSValue* weapon__getWeaponEffectiveAreaWeaponFrom(const ls::LSValue* weapon, const ls::LSValue* cell, const ls::LSValue* from) {

}

/*
 * Returns null or effect array
 */
ls::LSValue* weapon__getWeaponEffects() {
	// TODO
	return new ls::LSArray<ls::LSValue*>();
}
ls::LSValue* weapon__getWeaponEffectsWeapon(const ls::LSValue* weapon) {
	// TODO
	return new ls::LSArray<ls::LSValue*>();
}

/*
 * Deprecated: always 0
 */
int weapon__getWeaponFailure() {
	return 0;
}
int weapon__getWeaponFailure(const ls::LSValue*) {
	return 0;
}

/*
 * -1 or integer, always int
 */
int weapon__getWeaponMinRange() {
	return Simulator::entity->weapon->attack->min_range;
}
int weapon__getWeaponMinRangeWeapon(const ls::LSValue* weapon) {
	return ((Weapon*) weapon)->attack->min_range;
}
int weapon__getWeaponMaxRange() {
	return Simulator::entity->weapon->attack->max_range;
}
int weapon__getWeaponMaxRangeWeapon(const ls::LSValue* weapon) {
	return ((Weapon*) weapon)->attack->max_range;
}

ls::LSString* weapon__getWeaponName() {

}
ls::LSString* weapon__getWeaponNameWeapon(const ls::LSValue* weapon) {

}

bool weapon__isInlineWeapon() {

}
bool weapon__isInlineWeaponWeapon(const ls::LSValue* weapon) {

}

bool weapon__isWeapon(const ls::LSValue* weapon) {

}

int weapon__useWeapon(const ls::LSValue* entity) {

}

int weapon__useWeaponOnCell(const ls::LSValue* cell) {

}

bool weapon__weaponNeedLos(const ls::LSValue* weapon) {

}
