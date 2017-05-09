#include "Test.hpp"
#include <istream>
#include <fstream>
#include "../src/area/Area.hpp"
#include "../src/effect/Attack.hpp"

void Test::add_weapons(FightManager& manager) {
	std::string str = Util::read_file("test/data/weapons.json");
	Json weapons;
	try {
		weapons = Json::parse(str);
	} catch (std::exception& e) { // LCOV_EXCL_LINE
		assert(false); // LCOV_EXCL_LINE
	}
	// Add weapons
	for (auto& w : weapons) {
		auto id = w["id"];
		std::string name = w["name"];
		auto cost = w["cost"];
		auto effects = w["effects"];
		int area = w["area"];
		int launch_type = w["launch_type"];
		auto min_range = w["min_range"];
		auto max_range = w["max_range"];
		auto los = w["los"];
		auto weapon = new Weapon(id, name, cost, new Attack(min_range, max_range, (LaunchType) launch_type, (AreaType) area, los, effects, AttackType::WEAPON));
		manager.weapons.insert({name, weapon});

		// Add WEAPON_* constant in v1 VM
		auto p = ls::LSNumber::get(id);
		p->refs = 1;
		p->native = true;
		manager.vm_v1.add_constant(std::string("WEAPON_") + Util::toupper(name), ls::Type::NUMBER, p);
	}
}

void Test::add_chips(FightManager& manager) {
	std::string str = Util::read_file("test/data/chips.json");
	Json chips;
	try {
		chips = Json::parse(str);
	} catch (std::exception& e) { // LCOV_EXCL_LINE
		assert(false); // LCOV_EXCL_LINE
	}
	// Add chips
	for (auto& c : chips) {
		auto id = c["id"];
		std::string name = c["name"];
		auto cost = c["cost"];
		auto cooldown = c["cooldown"];
		auto team_cooldown = c["team_cooldown"];
		auto initial_cooldown = c["initial_cooldown"];
		auto effects = c["effects"];
		int area = c["area"];
		int launch_type = c["launch_type"];
		auto min_range = c["min_range"];
		auto max_range = c["max_range"];
		auto los = c["los"];
		auto chip = new Chip(id, name, cost, cooldown, team_cooldown, initial_cooldown, new Attack(min_range, max_range, (LaunchType) launch_type, (AreaType) area, los, effects, AttackType::CHIP));
		manager.chips.insert({name, chip});

		// Add CHIP_* constant in v1 VM
		auto p = ls::LSNumber::get(id);
		p->refs = 1;
		p->native = true;
		manager.vm_v1.add_constant(std::string("CHIP_") + Util::toupper(name), ls::Type::NUMBER, p);
	}
}
