#ifndef CLASS_WEAPONMODULE_HPP_
#define CLASS_WEAPONMODULE_HPP_

#include <leekscript.h>
#include "ItemModule.hpp"
#include "../fight/FightManager.hpp"
#include "colors.h"

class WeaponType : public ItemType {
public:
	const std::string getName() const { return "weapon"; };
	const std::string getClass() const { return "Weapon"; };
	virtual std::ostream& print(std::ostream& os) const override {
		os << BLUE_BOLD << "weapon" << END_COLOR;
		return os;
	}
};

class WeaponModule : public ls::Module {
public:
	WeaponModule(const FightManager& manager);
	virtual ~WeaponModule();

	static const ls::LSClass* weapon_clazz;
	static const std::shared_ptr<WeaponType> raw_type;
	static const ls::Type type;
	static const ls::Type const_type;
	static const ls::Type array_type;
};

bool weapon__canUseWeapon(const ls::LSValue* entity);
bool weapon__canUseWeaponWeapon(const ls::LSValue* weapon, const ls::LSValue* entity);
bool weapon__canUseWeaponOnCell(const ls::LSValue* cell);
bool weapon__canUseWeaponOnCellWeapon(const ls::LSValue* weapon, const ls::LSValue* cell);
ls::LSValue* weapon__getWeaponArea(const ls::LSValue* weapon);
int weapon__getWeaponCost();
int weapon__getWeaponCostWeapon(const ls::LSValue* weapon);
ls::LSValue* weapon__getWeaponEffectiveArea(const ls::LSValue* cell);
ls::LSValue* weapon__getWeaponEffectiveAreaWeapon(const ls::LSValue* weapon, const ls::LSValue* cell);
ls::LSValue* weapon__getWeaponEffectiveAreaWeaponFrom(const ls::LSValue* weapon, const ls::LSValue* cell, const ls::LSValue* from);
ls::LSValue* weapon__getWeaponEffects();
ls::LSValue* weapon__getWeaponEffectsWeapon(const ls::LSValue* weapon);
int weapon__getWeaponFailure();
int weapon__getWeaponFailure(const ls::LSValue*);
int weapon__getWeaponMaxRange(const ls::LSValue* weapon);
int weapon__getWeaponMinRange(const ls::LSValue* weapon);
ls::LSString* weapon__getWeaponName();
ls::LSString* weapon__getWeaponNameWeapon(const ls::LSValue* weapon);
bool weapon__isInlineWeapon();
bool weapon__isInlineWeaponWeapon(const ls::LSValue* weapon);
bool weapon__isWeapon(const ls::LSValue* weapon);
int weapon__useWeapon(const ls::LSValue* entity);
int weapon__useWeaponOnCell(const ls::LSValue* cell);
bool weapon__weaponNeedLos(const ls::LSValue* weapon);

#endif
