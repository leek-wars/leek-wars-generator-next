#include "ChipModule.hpp"
#include "../fight/FightManager.hpp"
#include "../util/Util.hpp"

const ls::LSClass* ChipModule::chip_clazz;
const ChipType* ChipModule::raw_type(new ChipType());
const ls::Type ChipModule::type(raw_type, ls::Nature::POINTER, true);
const ls::Type ChipModule::const_type(raw_type, ls::Nature::POINTER, true, false, true);
const ls::Type ChipModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, ChipModule::type, true);

jit_value_t Chip_SPARK(jit_function_t F) { return LS_CREATE_INTEGER(F, 1); }

ChipModule::ChipModule(const FightManager& manager) : Module("Chip") {

	for (const auto& w : manager.chips) {
		static_field(Util::toupper(w.first), ls::Type::INTEGER, [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
	}

	field("id", ls::Type::NUMBER_P);
	field("cost", ls::Type::NUMBER_P);
	field("name", ls::Type::STRING);

	/*
	 * V1
	 */
	method("_canUseChip", {{ls::Type::BOOLEAN, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &chip__canUseChip}});
	method("_canUseChipOnCell", {{ls::Type::BOOLEAN, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &chip__canUseChipOnCell}});
	method("_chipNeedLos", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &chip__chipNeedLos}});
	method("_getChipArea", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipArea}});
	method("_getChipCooldown", {{ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &chip__getChipCooldown}});
	method("_getChipCost", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipCost}});
	method("_getChipEffectiveAreaCell", {
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipEffectiveArea},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &chip__getChipEffectiveAreaCell},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER, ls::Type::POINTER}, (void*) &chip__getChipEffectiveAreaCellFrom},
	});
	method("_getChipEffects", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipEffects}});
	method("_getChipFailure", {{ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &chip__getChipFailure}});
	method("_getChipMaxRange", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipMaxRange}});
	method("_getChipMinRange", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getChipMinRange}});
	method("_getChipName", {{ls::Type::STRING, {ls::Type::POINTER}, (void*) &chip__getChipName}});
	method("_getCurrentCooldown", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &chip__getCurrentCooldown}});
	method("_isChip", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &chip__isChip}});
	method("_isInlineChip", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &chip__isInlineChip}});
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
	return ls::LSNull::get();
}

bool chip__isChip(const ls::LSValue* chip) {
	// TODO
}
bool chip__isInlineChip(const ls::LSValue* chip) {
	// TODO
}
