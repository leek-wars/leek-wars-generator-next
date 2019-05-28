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
		// Weapon.PISTOL : V2 version
		static_field(Util::toupper(w.second->name), ls::Type::integer(), [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
		// WEAPON_PISTOL : V1 version
		static_field(std::string("WEAPON_") + Util::toupper(w.second->name), ls::Type::integer(), [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
	}

	field("id", ls::Type::number());
	field("cost", ls::Type::number());
	field("name", ls::Type::string());

	// V1
	method("getWeaponCost", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponCost},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponCostWeapon},
		{ls::Type::integer(), {ls::Type::integer()}, (void*) &weapon__getWeaponCostWeapon_int},
	});
	method("getWeaponEffects", {
		{ls::Type::any(), {}, (void*) &weapon__getWeaponEffects},
		{ls::Type::any(), {ls::Type::any()}, (void*) &weapon__getWeaponEffectsWeapon},
		{ls::Type::any(), {ls::Type::integer()}, (void*) &weapon__getWeaponEffectsWeapon_int},
	});
	method("getWeaponMinRange", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponMinRange},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponMinRangeWeapon},
		{ls::Type::integer(), {ls::Type::integer()}, (void*) &weapon__getWeaponMinRangeWeapon_int},
	});
	method("getWeaponMaxRange", {
		{ls::Type::integer(), {}, (void*) &weapon__getWeaponMaxRange},
		{ls::Type::integer(), {ls::Type::any()}, (void*) &weapon__getWeaponMaxRangeWeapon},
		{ls::Type::integer(), {ls::Type::integer()}, (void*) &weapon__getWeaponMaxRangeWeapon_int},
	});
}

WeaponModule::~WeaponModule() {}

/*
 * V1 methods
 */
const Weapon* get_weapon(const ls::LSValue* x) {
	if (auto number = dynamic_cast<const ls::LSNumber*>(x)) {
		if (number->value == -1) return Simulator::entity->weapon;
		auto i = Simulator::fight->manager->weapons.find(number->value);
		if (i != Simulator::fight->manager->weapons.end()) {
			return i->second;
		}
	}
	return nullptr;
}
const Weapon* get_weapon_int(int x) {
	if (x == -1) return Simulator::entity->weapon;
	auto i = Simulator::fight->manager->weapons.find(x);
	if (i != Simulator::fight->manager->weapons.end()) {
		return i->second;
	}
	return nullptr;
}

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
	if (auto w = get_weapon(weapon)) return w->cost;
	return -1;
}
int weapon__getWeaponCostWeapon_int(int weapon) {
	if (auto w = get_weapon_int(weapon)) return w->cost;
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
ls::LSValue* get_effects(const Weapon* weapon) {
	auto effects = new ls::LSArray<ls::LSValue*>();
	for (const auto& effect : weapon->attack->effects) {
		auto e = new ls::LSArray<ls::LSValue*>();
		e->push_back(ls::LSNumber::get((int) effect.type));
		e->push_back(ls::LSNumber::get(effect.value1));
		e->push_back(ls::LSNumber::get(effect.value1 + effect.value2));
		e->push_back(ls::LSNumber::get(effect.turns));
		e->push_back(ls::LSNumber::get(effect.targets));
		e->push_back(ls::LSBoolean::get(effect.stackable));
		effects->push_back(e);
	}
	return effects;
}
ls::LSValue* weapon__getWeaponEffects() {
	if (not Simulator::entity->weapon) return ls::LSNull::get();
	return get_effects(Simulator::entity->weapon);
}
ls::LSValue* weapon__getWeaponEffectsWeapon(const ls::LSValue* weapon) {
	auto w = get_weapon(weapon);
	if (!w) return ls::LSNull::get();
	return get_effects(w);
}
ls::LSValue* weapon__getWeaponEffectsWeapon_int(int weapon) {
	auto w = get_weapon_int(weapon);
	if (!w) return ls::LSNull::get();
	return get_effects(w);
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
	if (auto w = get_weapon(weapon)) return w->attack->min_range;
	return -1;
}
int weapon__getWeaponMinRangeWeapon_int(int weapon) {
	if (auto w = get_weapon_int(weapon)) return w->attack->min_range;
	return -1;
}
int weapon__getWeaponMaxRange() {
	return Simulator::entity->weapon->attack->max_range;
}
int weapon__getWeaponMaxRangeWeapon(const ls::LSValue* weapon) {
	if (auto w = get_weapon(weapon)) return w->attack->max_range;
	return -1;
}
int weapon__getWeaponMaxRangeWeapon_int(int weapon) {
	if (auto w = get_weapon_int(weapon)) return w->attack->max_range;
	return -1;
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
