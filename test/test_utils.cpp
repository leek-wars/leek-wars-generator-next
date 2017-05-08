#include "Test.hpp"
#include <istream>
#include <fstream>

void Test::add_weapons(FightManager& manager) {
	// Parse json
	ifstream f;
	f.open("test/data/weapons.json");
	if (!f.good()) {
		return; // no file
	}
	stringstream j;
	j << f.rdbuf();
	std::string str = j.str();
	f.close();
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
		auto weapon = new Weapon(id, name, cost, new Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
		std::cout << "name: " << name << std::endl;
		manager.weapons.insert({name, weapon});

		// Add WEAPON_* constant in v1 VM
		auto p = ls::LSNumber::get(id);
		p->refs = 1;
		p->native = true;
		manager.vm_v1.add_constant(std::string("WEAPON_") + Util::toupper(name), ls::Type::NUMBER, p);
	}
}
