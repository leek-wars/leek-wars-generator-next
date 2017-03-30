#include "Test.hpp"

void Test::test_fight() {

	header("Fight");

	ls::VM vm;
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());

	Fight fight;

	// Create some weapons
	Weapon pistol(37, "Pistol", 3, Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
	Weapon laser(42, "Laser", 6, Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));

	// Create some chips
	Chip fortress(29, "Fortress", 6, 4, false, 0, Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	Team* team1 = new Team();
	// Entity 1
	AI* ai1 = new AI(Util::read_file("test/ai/color.ls"));
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

	Team* team2 = new Team();
	// Entity 2
	AI* ai2 = new AI(Util::read_file("test/ai/hangry.ls"));
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {&laser};
	leek2->setWeapons(weapons2);
	vector<Chip*> chips2 = {&fortress};
	leek2->setChips(chips2);
	team2->add_entity(leek2);
	leek2->team = 1;

	fight.teams = {team1, team2};

	fight.map = new Map(18, 18, 25, {team1, team2});

	// Run the fight
	Report* report = fight.start(vm);
	std::cout << report << std::endl;
}

void Test::test_generateCritical() {

	header("generateCritical");

	Fight fight;
	auto leek1 = new Leek(&fight, "Franklin", 297, nullptr);
	Characteristics characs1;
	characs1.set(Characteristic::AGILITY, 0);
	leek1->setCharacteristics(characs1);

	auto leek2 = new Leek(&fight, "Franklin", 297, nullptr);
	Characteristics characs2;
	characs2.set(Characteristic::AGILITY, 1000);
	leek2->setCharacteristics(characs2);

	assert(fight.generateCritical(leek1) == 0);
	assert(fight.generateCritical(leek2) == 1);
}
