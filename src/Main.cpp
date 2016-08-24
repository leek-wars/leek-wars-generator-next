#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

#include <leekscript/src/leekscript.h>

#include "../benchmark/Benchmark.hpp"
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

int main() {

	cout << "~~ leek-wars-simulator ~~" << endl;

	auto start_time = chrono::high_resolution_clock::now();

	srand(time(NULL));

	ls::VM vm;
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());

	// Create some weapons
	Weapon pistol(37, "Pistol", 3, Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
	Weapon laser(42, "Laser", 6, Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));

	// Create some chips
	Chip fortress(29, "Fortress", 6, 4, false, 0, Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	// Create fight
	Fight fight;

	/*
	 * Team 1
	 */
	Team* team1 = new Team();

	// Entity 1
	AI* ai1 = new AI(Util::read_file("ai/basic.ls"));
	Leek* leek1 = new Leek(&fight, "Trevor", 300, ai1);
	Characteristics characs1;
	characs1.set(Characteristic::LIFE, 3200);
	characs1.set(Characteristic::TP, 2000);
	characs1.set(Characteristic::MP, 5);
	characs1.set(Characteristic::STRENGTH, 978);
	leek1->setCharacteristics(characs1);
	vector<Weapon*> weapons1 = {&pistol, &laser};
	leek1->setWeapons(weapons1);
	vector<Chip*> chips1 = {&fortress};
	leek1->setChips(chips1);
	team1->add_entity(leek1);
	leek1->team = 0;

	/*
	 * Team 2
	 */
	Team* team2 = new Team();

	// Entity 2
	AI* ai2 = new AI(Util::read_file("ai/color.ls"));
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::TP, 2000);
	characs2.set(Characteristic::MP, 5);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {&laser};
	leek2->setWeapons(weapons2);
	team2->add_entity(leek2);
	leek2->team = 1;

	fight.teams = {team1, team2};

	fight.map = new Map(18, 18, 30, {team1, team2});

//	vector<Cell*> path = fight.map->get_path(leek1->cell, {leek2->cell}, {});
//	fight.map->draw_path(path, leek1->cell, leek2->cell);


	// Run the fight
	Report* report = fight.start(vm);

//	fight.map->print();
//	cout << fight.map->line_of_sight(fight.map->cells[50], fight.map->cells[500], {}) << endl;

	// Print the report
	cout << report << endl;

	std::ofstream report_file("fight.json");

	report_file << report << std::endl;


//	vector<Cell*> path2 = fight.map->get_path(fight.map->cells[51], {fight.map->cells[561]}, {});
//	fight.map->draw_path(path2, fight.map->cells[51], fight.map->cells[561]);

	// LeekModule().generate_doc(cout, string("src/doc/Leek_fr.json"));

	// vm.execute("var l = {life: 12} Leek.getLife(l)", "{}", ExecMode::NORMAL);


	auto end_time = chrono::high_resolution_clock::now();
	long time_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	double time_ms = (((double) time_ns / 1000) / 1000);
	cout << "total time: " << time_ms << " ms" << endl;

//	Benchmark::pathfinding();

	delete report;

	return 0;
}
