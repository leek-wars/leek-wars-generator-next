#include "WeaponModule.hpp"
#include "../util/Util.hpp"

const ls::LSClass* WeaponModule::weapon_clazz;
const WeaponType* WeaponModule::raw_type(new WeaponType());
const ls::Type WeaponModule::type(raw_type, ls::Nature::POINTER, true);
const ls::Type WeaponModule::const_type(raw_type, ls::Nature::POINTER, true, false, true);
const ls::Type WeaponModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, WeaponModule::type, true);

WeaponModule::WeaponModule(const FightManager& manager) : Module("Weapon") {

	for (const auto& w : manager.weapons) {
		static_field(Util::toupper(w.first), ls::Type::INTEGER, [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
	}

	field("id", ls::Type::NUMBER_P);
	field("cost", ls::Type::NUMBER_P);
	field("name", ls::Type::STRING);
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

}
int weapon__getWeaponCostWeapon(const ls::LSValue* weapon) {

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

}
ls::LSValue* weapon__getWeaponEffectsWeapon(const ls::LSValue* weapon) {

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
int weapon__getWeaponMaxRange(const ls::LSValue* weapon) {

}
int weapon__getWeaponMinRange(const ls::LSValue* weapon) {

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
