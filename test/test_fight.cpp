#include "Test.hpp"
#include "../src/fight/FightLoader.hpp"

void Test::test_fight() {

	header("Fight > general");
	Util::log_enabled = false;

	auto fight = FightLoader::load(manager, "test/fight/fight.json");
	auto entity = fight->teams[0]->entities[0];
	test_ai(fight, entity, "Fight.getEntity().name", "'Poireau'");
	test_ai(fight, entity, "Fight.getEntity().life", "5000");
	test_ai(fight, entity, "Fight.getEntity().tp", "12");
	test_ai(fight, entity, "Fight.getEntity().mp", "6");
	test_ai(fight, entity, "Fight.getEntity().strength", "500");
	test_ai(fight, entity, "Fight.getEntity().level", "301");
	test_ai(fight, entity, "Fight.getEntity().cell.class", "<class Cell>");
	test_ai(fight, entity, "Fight.getEntity().weapons", "[<Weapon m_laser>]");
	test_ai(fight, entity, "Fight.getEntity().weapon", "null");
	test_ai(fight, entity, "Fight.getEntity().chips", "[<Chip protein>]");
	test_ai(fight, entity, "Fight.getEntity().damageReturn", "0");
	test_ai(fight, entity, "Fight.getEntity().frequency", "0");
	test_ai(fight, entity, "Fight.getEntity().relativeShield", "0");
	test_ai(fight, entity, "Fight.getEntity().absoluteShield", "0");
	test_ai(fight, entity, "Fight.getEntity().science", "0");
	test_ai(fight, entity, "Fight.getEntity().resistance", "0");
	test_ai(fight, entity, "Fight.getEntity().magic", "0");
	test_ai(fight, entity, "Fight.getEntity().wisdom", "0");
	test_ai(fight, entity, "Fight.getEntity().agility", "0");
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
	manager.start(*fight, [&](Report* report) {
		// std::cout << "-------------- report ----------------" << std::endl;
		// std::cout << report << std::endl;

		// run_fight_browser(report);

		test("report != nullptr", report != nullptr, true);

		delete report;
	});
}
