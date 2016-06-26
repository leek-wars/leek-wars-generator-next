/*
 * ChipModule.hpp
 *
 *  Created on: May 4, 2016
 *      Author: pierre
 */

#ifndef MODULE_CHIPMODULE_HPP_
#define MODULE_CHIPMODULE_HPP_

#include <leekscript.h>
#include "ItemModule.hpp"

class ChipType : public ItemType {
public:
	const std::string getName() const { return "Chip"; };
};


class ChipModule : public ls::Module {
public:
	ChipModule();
	virtual ~ChipModule();

	static const ls::LSClass* chip_clazz;
	static const ls::Type type;
	static const ls::Type array_type;
};

bool chip__canUseChip(const ls::LSValue* chip, const ls::LSValue* entity);
bool chip__canUseChipOnCell(const ls::LSValue* chip, const ls::LSValue* cell);
bool chip__chipNeedLos(const ls::LSValue* chip);
ls::LSValue* chip__getChipArea(const ls::LSValue* chip);
int chip__getChipCooldown(const ls::LSValue* chip);
ls::LSValue* chip__getChipCost(const ls::LSValue* chip);
ls::LSValue* chip__getChipEffectiveArea(const ls::LSValue* chip);
ls::LSValue* chip__getChipEffectiveAreaCell(const ls::LSValue* chip, const ls::LSValue* cell);
ls::LSValue* chip__getChipEffectiveAreaCellFrom(const ls::LSValue* chip, const ls::LSValue* cell, const ls::LSValue* from);
ls::LSValue* chip__getChipEffects(const ls::LSValue* chip);
int chip__getChipFailure(const ls::LSValue* chip);
ls::LSValue* chip__getChipMaxRange(const ls::LSValue* chip);
ls::LSValue* chip__getChipMinRange(const ls::LSValue* chip);
ls::LSString* chip__getChipName(const ls::LSValue* chip);
ls::LSValue* chip__getCurrentCooldown(const ls::LSValue*);
bool chip__isChip(const ls::LSValue* chip);
bool chip__isInlineChip(const ls::LSValue* chip);

#endif /* MODULE_CHIPMODULE_HPP_ */
