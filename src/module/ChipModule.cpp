/*
 * ChipModule.cpp
 *
 *  Created on: May 4, 2016
 *      Author: pierre
 */

#include "ChipModule.hpp"

const ls::LSClass* ChipModule::chip_clazz;
const ls::Type ChipModule::type(new ChipType(), ls::Nature::POINTER, true);
const ls::Type ChipModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, ChipModule::type, true);

ChipModule::ChipModule() : Module("Chip") {

	static_field("SPARK", Type::INTEGER_P, "1");

	/*
	 * V1
	 */
	static_method("_canUseChip", Type::BOOLEAN, {Type::POINTER, Type::POINTER}, (void*) &chip__canUseChip);
	static_method("_canUseChipOnCell", Type::BOOLEAN, {Type::POINTER, Type::POINTER}, (void*) &chip__canUseChipOnCell);
	static_method("_chipNeedLos", Type::BOOLEAN, {Type::POINTER}, (void*) &chip__chipNeedLos);
	static_method("_getChipArea", Type::POINTER, {Type::POINTER}, (void*) &chip__getChipArea);
	static_method("_getChipCooldown", Type::INTEGER, {Type::POINTER}, (void*) &chip__getChipCooldown);
	static_method("_getChipCost", Type::POINTER, {Type::POINTER}, (void*) &chip__getChipCost);
	static_method("_getChipEffectiveAreaCell", {
		{Type::POINTER, {Type::POINTER}, (void*) &chip__getChipEffectiveArea},
		{Type::POINTER, {Type::POINTER, Type::POINTER}, (void*) &chip__getChipEffectiveAreaCell},
		{Type::POINTER, {Type::POINTER, Type::POINTER, Type::POINTER}, (void*) &chip__getChipEffectiveAreaCellFrom},
	});
	static_method("_getChipEffects", Type::POINTER, {Type::POINTER}, (void*) &chip__getChipEffects);
	static_method("_getChipFailure", Type::INTEGER, {Type::POINTER}, (void*) &chip__getChipFailure);
	static_method("_getChipMaxRange", Type::POINTER, {Type::POINTER}, (void*) &chip__getChipMaxRange);
	static_method("_getChipMinRange", Type::POINTER, {Type::POINTER}, (void*) &chip__getChipMinRange);
	static_method("_getChipName", Type::STRING, {Type::POINTER}, (void*) &chip__getChipName);
	static_method("_getCurrentCooldown", Type::POINTER, {Type::POINTER}, (void*) &chip__getCurrentCooldown);
	static_method("bool isChip", Type::BOOLEAN, {Type::POINTER}, (void*) &chip__isChip);
	static_method("bool isInlineChip", Type::BOOLEAN, {Type::POINTER}, (void*) &chip__isInlineChip);
}

ChipModule::~ChipModule() {}

/*
 * V1 methods
 */
bool chip__canUseChip(const ls::LSValue* chip, const ls::LSValue* entity) {
	// TODO
}
bool chip__canUseChipOnCell(const ls::LSValue* chip, const ls::LSValue* cell) {
	// TODO
}
bool chip__chipNeedLos(const ls::LSValue* chip) {
	// TODO
}
/*
 * Null or int
 */
ls::LSValue* chip__getChipArea(const ls::LSValue* chip) {
	// TODO
}
/*
 * 0 for invalid chip, always integer
 */
int chip__getChipCooldown(const ls::LSValue* chip) {
	// TODO
}
/*
 * Null or integer
 * Cell 0 if argument cell is null.
 */
ls::LSValue* chip__getChipCost(const ls::LSValue* chip) {
	// TODO
}

ls::LSValue* chip__getChipEffectiveArea(const ls::LSValue* chip) {
	// TODO
	// Weird case that existed in the V1 : no target cell is considered the cell 0 (null -> 0)
}
ls::LSValue* chip__getChipEffectiveAreaCell(const ls::LSValue* chip, const ls::LSValue* cell) {
	// TODO
	// Cell 0 if argument cell is null.
}
ls::LSValue* chip__getChipEffectiveAreaCellFrom(const ls::LSValue* chip, const ls::LSValue* cell, const ls::LSValue* from) {
	// TODO
	// Cell 0 if argument cell is null.
}

/*
 * Null or object array
 */
ls::LSValue* chip__getChipEffects(const ls::LSValue* chip) {
	// TODO
}

int chip__getChipFailure(const ls::LSValue* chip) {
	return 0; // Deprecated, always 0
}

/*
 * integer or null
 */
ls::LSValue* chip__getChipMaxRange(const ls::LSValue* chip) {
	// TODO
}
ls::LSValue* chip__getChipMinRange(const ls::LSValue* chip) {
	// TODO
}

/*
 * empty string or name, always string
 */
ls::LSString* chip__getChipName(const ls::LSValue* chip) {
	// TODO
}

/*
 * Deprecated, always null
 */
ls::LSValue* chip__getCurrentCooldown(const ls::LSValue*) {
	return ls::LSNull::null_var;
}

bool chip__isChip(const ls::LSValue* chip) {
	// TODO
}
bool chip__isInlineChip(const ls::LSValue* chip) {
	// TODO
}
