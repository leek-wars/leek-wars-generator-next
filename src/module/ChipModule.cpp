#include "ChipModule.hpp"
#include "../fight/FightManager.hpp"
#include "../util/Util.hpp"

const ls::LSClass* ChipModule::chip_clazz;
const std::shared_ptr<ChipType> ChipModule::raw_type = std::make_shared<ChipType>();
const ls::Type ChipModule::type(raw_type, true);
const ls::Type ChipModule::const_type(raw_type, true, false, true);
const ls::Type ChipModule::array_type = ls::Type::array(ChipModule::type);

ls::Compiler::value Chip_SPARK(ls::Compiler& c) { return c.new_integer(1); }

ChipModule::ChipModule(const FightManager& manager) : Module("Chip") {

	for (const auto& w : manager.chips) {
		static_field(Util::toupper(w.second->name), ls::Type::integer(), [&](ls::Compiler& c) {
			return c.new_integer(w.second->id);
		});
	}

	field("id", ls::Type::number());
	field("cost", ls::Type::number());
	field("name", ls::Type::string());

	/*
	 * V1
	 */
	method("_canUseChip", {{ls::Type::boolean(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__canUseChip}});
	method("_canUseChipOnCell", {{ls::Type::boolean(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__canUseChipOnCell}});
	method("_chipNeedLos", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__chipNeedLos}});
	method("_getChipArea", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipArea}});
	method("_getChipCooldown", {{ls::Type::integer(), {ls::Type::any()}, (void*) &chip__getChipCooldown}});
	method("_getChipCost", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipCost}});
	method("_getChipEffectiveAreaCell", {
		{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipEffectiveArea},
		{ls::Type::any(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__getChipEffectiveAreaCell},
		{ls::Type::any(), {ls::Type::any(), ls::Type::any(), ls::Type::any()}, (void*) &chip__getChipEffectiveAreaCellFrom},
	});
	method("_getChipEffects", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipEffects}});
	method("_getChipFailure", {{ls::Type::integer(), {ls::Type::any()}, (void*) &chip__getChipFailure}});
	method("_getChipMaxRange", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipMaxRange}});
	method("_getChipMinRange", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipMinRange}});
	method("_getChipName", {{ls::Type::string(), {ls::Type::any()}, (void*) &chip__getChipName}});
	method("_getCurrentCooldown", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getCurrentCooldown}});
	method("_isChip", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__isChip}});
	method("_isInlineChip", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__isInlineChip}});
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
