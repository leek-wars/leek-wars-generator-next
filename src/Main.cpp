#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <leekscript/src/leekscript.h>

#include "util/Util.hpp"
#include "fight/Fight.hpp"
#include "map/Map.hpp"
#include "entity/Team.hpp"
#include "entity/Leek.hpp"
#include "item/Chip.hpp"
#include "area/AreaSingleCell.hpp"
#include "module/FightModule.hpp"
#include "module/EntityModule.hpp"
#include "module/MapModule.hpp"
#include "module/CellModule.hpp"
#include "module/LeekModule.hpp"
#include "module/WeaponModule.hpp"
#include "module/ColorModule.hpp"
#include "module/ChipModule.hpp"
#include "fight/FightLoader.hpp"
#include "fight/FightManager.hpp"

using namespace std;

int main(int argc, char** argv) {

	cout << "~~ leek-wars-simulator v1.0 ~~" << endl;

	// Global initialization
	srand(time(NULL));
	auto null_value = ls::LSNull::create();
	auto true_value = ls::LSBoolean::create(true);
	auto false_value = ls::LSBoolean::create(false);
	ls::LSNull::set_null_value(null_value);
	ls::LSBoolean::set_true_value(true_value);
	ls::LSBoolean::set_false_value(false_value);

	// Load a fight file?
	if (argc == 2) {
		std::string fight_file(argv[1]);
		std::cout << "load fight '" << fight_file << "'..." << std::endl;
		auto fight = FightLoader::load(fight_file);
		auto report = FightManager().start(*fight);
		std::cout << report << std::endl;
		delete report;
		return 0;
	}

	auto start_time = chrono::high_resolution_clock::now();

	ls::VM vm;
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());

	ls::VM vmv1(true);
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());

	// Create some weapons
	Weapon pistol(37, "Pistol", 3, new Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
	Weapon laser(42, "Laser", 6, new Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));

	// Create some chips
	Chip fortress(29, "Fortress", 6, 4, false, 0, new Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	// Create fight
	Fight fight;

	Team* team1 = new Team();
	// Entity 1
	AI* ai1 = new AI(Util::read_file("test/ai/hangry.ls"), "hangry.ls");
	Leek* leek1 = new Leek(&fight, "Trevor", 300, ai1);
	Characteristics characs1;
	characs1.set(Characteristic::LIFE, 3200);
	characs1.set(Characteristic::TP, 2000);
	characs1.set(Characteristic::MP, 100);
	characs1.set(Characteristic::STRENGTH, 978);
	leek1->setCharacteristics(characs1);
	vector<Weapon*> weapons1 = {&pistol, &laser};
	leek1->setWeapons(weapons1);
	vector<Chip*> chips1 = {&fortress};
	leek1->setChips(chips1);
	team1->add_entity(leek1);
	leek1->team = 0;

	Team* team2 = new Team();
	// Entity 2
	AI* ai2 = new AI(Util::read_file("test/ai/color.ls"), "color.ls");
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::TP, 2000);
	characs2.set(Characteristic::MP, 100);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {&laser};
	leek2->setWeapons(weapons2);
	team2->add_entity(leek2);
	leek2->team = 1;

	fight.teams = {team1, team2};

	fight.map.reset(new Map(18, 18, 30, {team1, team2}));

	// Run the fight
	Report* report = fight.start(vm, vmv1);

	// Print the report
	cout << report << endl;

	auto end_time = chrono::high_resolution_clock::now();
	long time_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	double time_ms = (((double) time_ns / 1000) / 1000);
	cout << "total time: " << time_ms << " ms" << endl;

	// Start a browser with the fight
	std::ofstream report_file("fight.json");
	report_file << report << std::endl;
	system("chromium-browser http://localhost:8012/fight/local");

	delete report;

	return 0;
}
