#include "Test.hpp"

void Test::test_fight() {

	header("Fight");

	Fight fight;

	// Create some weapons
	Weapon pistol(37, "Pistol", 3, new Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
	Weapon laser(42, "Laser", 6, new Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));

	// Create some chips
	Chip fortress(29, "Fortress", 6, 4, false, 0, new Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	Team* team1 = new Team();
	// Entity 1
	AI* ai1 = new AI(Util::read_file("test/ai/color.ls"), "color.ls");
	Leek* leek1 = new Leek(&fight, "Trevor", 300, ai1);
	Characteristics characs1;
	characs1.set(Characteristic::LIFE, 3200);
	characs1.set(Characteristic::TP, 2000);
	characs1.set(Characteristic::MP, 10);
	characs1.set(Characteristic::STRENGTH, 978);
	leek1->setCharacteristics(characs1);
	vector<Weapon*> weapons1 = {manager.weapons["pistol"], manager.weapons["laser"]};
	leek1->setWeapons(weapons1);
	vector<Chip*> chips1 = {&fortress};
	leek1->setChips(chips1);
	team1->add_entity(leek1);
	leek1->team = 0;

	Team* team2 = new Team();
	// Entity 2
	AI* ai2 = new AI(Util::read_file("test/ai/hangry.ls"), "hangry.ls");
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::TP, 2000);
	characs2.set(Characteristic::MP, 10);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {manager.weapons["laser"]};
	leek2->setWeapons(weapons2);
	vector<Chip*> chips2 = {&fortress};
	leek2->setChips(chips2);
	team2->add_entity(leek2);
	leek2->team = 1;
	// Entity 3
	auto ai3 = new AI(Util::read_file("test/ai/basic.ls"), "basic.ls");
 	auto leek3 = new Leek(&fight, "Hodor", 297, ai3);
	Characteristics characs3;
	characs3.set(Characteristic::LIFE, 3900);
	characs3.set(Characteristic::TP, 2000);
	characs3.set(Characteristic::MP, 10);
	characs3.set(Characteristic::STRENGTH, 470);
	leek3->setCharacteristics(characs3);
	leek3->setWeapons({manager.weapons["pistol"], manager.weapons["laser"]});
	leek3->setChips({&fortress});
	team2->add_entity(leek3);
	leek3->team = 1;

	fight.teams = {team1, team2};

	fight.map.reset(new Map(18, 18, 25, {team1, team2}));

	// Run the fight
	auto report = manager.start(fight);
	std::cout << "-------------- report ----------------" << std::endl;
	std::cout << report << std::endl;
	delete report;
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

	delete leek1;
	delete leek2;
}

void Test::test_fight_v1() {

	header("Fight v1");

	Fight fight;

	// Create some chips
	Chip fortress(29, "Fortress", 6, 4, false, 0, new Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	Team* team1 = new Team();
	// Entity 1
	AI* ai1 = new AI(Util::read_file("test/ai/v1/example_ai.leek"), "example_ai.leek", true);
	Leek* leek1 = new Leek(&fight, "Trevor", 300, ai1);
	Characteristics characs1;
	characs1.set(Characteristic::LIFE, 3200);
	characs1.set(Characteristic::TP, 2000);
	characs1.set(Characteristic::MP, 10);
	characs1.set(Characteristic::STRENGTH, 978);
	leek1->setCharacteristics(characs1);
	vector<Weapon*> weapons1 = {manager.weapons["pistol"], manager.weapons["laser"]};
	leek1->setWeapons(weapons1);
	vector<Chip*> chips1 = {&fortress};
	leek1->setChips(chips1);
	team1->add_entity(leek1);
	leek1->team = 0;

	Team* team2 = new Team();
	// Entity 2
	AI* ai2 = new AI(Util::read_file("test/ai/v1/example_ai.leek"), "example_ai.leek", true);
	Leek* leek2 = new Leek(&fight, "Franklin", 297, ai2);
	Characteristics characs2;
	characs2.set(Characteristic::LIFE, 3900);
	characs2.set(Characteristic::TP, 2000);
	characs2.set(Characteristic::MP, 10);
	characs2.set(Characteristic::STRENGTH, 470);
	leek2->setCharacteristics(characs2);
	vector<Weapon*> weapons2 = {manager.weapons["laser"]};
	leek2->setWeapons(weapons2);
	vector<Chip*> chips2 = {&fortress};
	leek2->setChips(chips2);
	team2->add_entity(leek2);
	leek2->team = 1;

	fight.teams = {team1, team2};

	fight.map.reset(new Map(18, 18, 25, {team1, team2}));

	// Run the fight
	auto report = manager.start(fight);
	std::cout << "-------------- report ----------------" << std::endl;
	std::cout << report << std::endl;
	delete report;
}
