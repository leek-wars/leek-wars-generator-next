#include "Test.hpp"
#include "../src/fight/FightLoader.hpp"

void Test::test_fight() {

	header("Fight");
	Util::log_enabled = false;

	auto fight = FightLoader::load(manager, "test/fight/fight.json");
	auto entity = fight->teams[0]->entities[0];

	header("Fight > entity");
	test_ai(fight, entity, "Fight.getEntity().name", "'Poireau'");
	test_ai(fight, entity, "Fight.getEntity().life", "5000");
	test_ai(fight, entity, "Fight.getEntity().tp", "12");
	test_ai(fight, entity, "Fight.getEntity().mp", "6");
	test_ai(fight, entity, "Fight.getEntity().strength", "500");
	test_ai(fight, entity, "Fight.getEntity().level", "301");
	test_ai(fight, entity, "Fight.getEntity().cell.class", "<class Cell>");
	test_ai(fight, entity, "Fight.getEntity().weapons", "[<Weapon m_laser>]");
	test_ai(fight, entity, "Fight.getEntity().weapons.first()", "<Weapon m_laser>");
	test_ai(fight, entity, "Fight.getEntity().weapons.size()", "1");
	test_ai(fight, entity, "Fight.getEntity().weapons ~~ x -> x.name", "['m_laser']");
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

	header("Fight > fight functions");
	test_ai(fight, entity, "Fight.getEntity().getClosestEnemy().name in ['Bob', 'Boss', 'Donald']", "true");
	test_ai(fight, entity, "Fight.getEntity().getClosestAlly().name", "'Yolo'");

	header("Fight > field");
	test_ai(fight, entity, "Field", "<class Field>");
	test_ai(fight, entity, "Field.obstacles.class", "<class Array>");
	test_ai(fight, entity, "Field.obstacles.size() in [30..100]", "true");
	test_ai(fight, entity, "Field.cell(0, 0)", "<Cell 306>");
	test_ai(fight, entity, "Field.cell(-17, 0)", "<Cell 595>");
	test_ai(fight, entity, "Field.cell(17, 0)", "<Cell 17>");
	test_ai(fight, entity, "Field.cell(0, 17)", "<Cell 612>");
	test_ai(fight, entity, "Field.cell(0, -17)", "<Cell 0>");
	test_ai(fight, entity, "let me = Fight.getEntity() Field.lineOfSight(me.cell, me.getClosestEnemy().cell).class", "<class Boolean>");
	test_ai(fight, entity, "let path = Field.path(Fight.getEntity().cell, Field.cell(0, 0)) path.size() == 0 || path.first() == Fight.getEntity().cell", "true");

	header("Fight > movement");
	test_ai(fight, entity, "var me = Fight.getEntity(), e = me.getClosestEnemy(), d = me.cell.distance(e.cell) me.moveToward(e) me.cell.distance(e.cell) <= d", "true");
	test_ai(fight, entity, "var me = Fight.getEntity(), e = me.getClosestEnemy(), d = me.cell.distance(e.cell) me.moveToward(e, 100) me.cell.distance(e.cell) <= d", "true");
	test_ai(fight, entity, "var me = Fight.getEntity(), c = Field.cell(0, 0), d = me.cell.distance(c) me.moveToward(c, 100) me.cell.distance(c) <= d", "true");
	test_ai(fight, entity, "var me = Fight.getEntity(), c = Field.cell(0, 0), d = me.cell.distance(c) me.moveToward(c) me.cell.distance(c) <= d", "true");
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
