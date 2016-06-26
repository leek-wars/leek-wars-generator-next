#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Test.hpp"

#include "../src/util/Util.hpp"
#include "../src/fight/Fight.hpp"
#include "../src/map/Map.hpp"
#include "../src/entity/Team.hpp"
#include "../src/entity/Leek.hpp"
#include "../src/item/Chip.hpp"
#include "../src/area/AreaSingleCell.hpp"

#include "../src/module/FightModule.hpp"
#include "../src/module/EntityModule.hpp"
#include "../src/module/MapModule.hpp"
#include "../src/module/CellModule.hpp"
#include "../src/module/LeekModule.hpp"
#include "../src/module/WeaponModule.hpp"
#include "../src/module/ColorModule.hpp"
#include "../src/module/ChipModule.hpp"

using namespace std;

Test::Test() {
	total = 0;
	success = 0;
	exeTime = 0;
}

void Test::tests() {

	clock_t begin = clock();
	exeTime = 0;

	/*
	 * General
	 */
	header("General");

	test("ai.ls", 12, 12);


	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Total : " << total << ", succès : " << success << ", erreurs : " << (total - success) << endl;
	cout << "Total time : " << elapsed_secs * 1000 << " ms, execution time : " << (exeTime / CLOCKS_PER_SEC) * 1000 << " ms" << endl;
	cout << "------------------------------------------------" << endl;
}


// Read file


std::string Test::run_fight() {

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
	AI* ai1 = new AI(Util::read_file("ai1.ls"));
	Leek* leek1 = new Leek(&fight, "Trevor", 300, ai1);
	Characteristics characs1;
	characs1.set(Characteristic::LIFE, 3200);
	characs1.set(Characteristic::TP, 2000);
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
	AI* ai2 = new AI(Util::read_file("ai2.ls"));
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {&laser};
	leek2->setWeapons(weapons2);
	team2->add_entity(leek2);
	leek2->team = 1;

	fight.teams = {team1, team2};

	fight.map = new Map(18, 18, 100, {/*team1, team2*/});

	// Run the fight
	Report* report = fight.start(vm);
	ostringstream oss;
	oss << report;
	return oss.str();
}

void Test::header(string text) {
	cout << "----------------" << endl;
	cout << text << endl;
	cout << "----------------" << endl;
}

template <typename T>
void Test::test(std::string message, T expected, T res) {

	total++;

	if (expected != res) {
		cout << "FAUX : " << message << "  =/=>  " << expected << "  got  " << res << endl;
	} else {
		cout << "OK   : " << message << "  ===>  " << res << endl;
		success++;
	}
}

Test::~Test() {}
