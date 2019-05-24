#include "ChipModule.hpp"
#include "../fight/FightManager.hpp"
#include "../util/Util.hpp"
#include "../fight/Simulator.hpp"

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
	method("canUseChip", {{ls::Type::boolean(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__canUseChip}});
	method("canUseChipOnCell", {{ls::Type::boolean(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__canUseChipOnCell}});
	method("chipNeedLos", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__chipNeedLos}});
	method("getChipArea", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipArea}});
	method("getChipCooldown", {{ls::Type::integer(), {ls::Type::any()}, (void*) &chip__getChipCooldown}});
	method("getChipCost", {
		{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipCost, ls::Method::NATIVE}
	});
	method("getChipEffectiveAreaCell", {
		{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipEffectiveArea},
		{ls::Type::any(), {ls::Type::any(), ls::Type::any()}, (void*) &chip__getChipEffectiveAreaCell},
		{ls::Type::any(), {ls::Type::any(), ls::Type::any(), ls::Type::any()}, (void*) &chip__getChipEffectiveAreaCellFrom},
	});
	method("getChipEffects", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipEffects}});
	method("getChipFailure", {{ls::Type::integer(), {ls::Type::any()}, (void*) &chip__getChipFailure}});
	method("getChipMaxRange", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipMaxRange}});
	method("getChipMinRange", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getChipMinRange}});
	method("getChipName", {{ls::Type::string(), {ls::Type::any()}, (void*) &chip__getChipName}});
	method("getCurrentCooldown", {{ls::Type::any(), {ls::Type::any()}, (void*) &chip__getCurrentCooldown}});
	method("isChip", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__isChip}});
	method("isInlineChip", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &chip__isInlineChip}});
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
 * return: Null or integer (different from getWeaponCost)
 */
ls::LSValue* chip__getChipCost(const ls::LSValue* chip) {
	if (auto number = dynamic_cast<const ls::LSNumber*>(chip)) {
		auto i = Simulator::fight->manager->chips.find(number->value);
		if (i != Simulator::fight->manager->chips.end()) {
			return ls::LSNumber::get(i->second->cost);
		}
	}
	return ls::LSNull::get();
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
