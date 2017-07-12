#include "Test.hpp"
#include "../src/fight/FightLoader.hpp"

void Test::test_fight() {

	header("Fight > general");
	Util::log_enabled = false;

	auto fight = FightLoader::load(manager, "test/fight/fight.json");
	auto entity = fight->teams[0]->entities[0];
	test_ai(fight, entity, "Fight.getEntity().name", "'Poireau'");
	test_ai(fight, entity, "Fight.getEntity().life", "500");
	test_ai(fight, entity, "Fight.getEntity().weapons", "[<Weapon m_laser>]");
	test_ai(fight, entity, "Fight.getEntity().chips", "[<Chip protein>]");
}

void Test::test_generateCritical() {

	header("Fight > generateCritical");
	Util::log_enabled = true;

	Fight fight;
	auto leek1 = new Leek(&fight, "Franklin", 297, nullptr);
	Characteristics characs1;
	characs1.set(Characteristic::AGILITY, 0);
	leek1->setCharacteristics(characs1);

	auto leek2 = new Leek(&fight, "Franklin", 297, nullptr);
	Characteristics characs2;
	characs2.set(Characteristic::AGILITY, 1000);
	leek2->setCharacteristics(characs2);

	test("fight.generateCritical(leek1)", fight.generateCritical(leek1), false);
	test("fight.generateCritical(leek2)", fight.generateCritical(leek2), true);

	delete leek1;
	delete leek2;
}

void Test::test_fight_v1() {

	header("Fight > v1");
	Util::log_enabled = false;

	auto fight = FightLoader::load(manager, "test/fight/fight_v1.json");

	// Run the fight
	manager.start(*fight, [](Report* report) {
		// std::cout << "-------------- report ----------------" << std::endl;
		// std::cout << report << std::endl;

		// run_fight_browser(report);

		delete report;
	});
}
