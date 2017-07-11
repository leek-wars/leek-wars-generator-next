#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <string>
#include <chrono>

#include "../src/fight/Fight.hpp"
#include "../src/entity/Leek.hpp"
#include "../src/util/Util.hpp"
#include "../src/fight/Fight.hpp"
#include "../src/field/Field.hpp"
#include "../src/entity/Team.hpp"
#include "../src/entity/Leek.hpp"
#include "../src/item/Chip.hpp"
#include "../src/area/AreaSingleCell.hpp"
#include "../src/fight/FightManager.hpp"

class Test {

	FightManager manager;
	int total;
	int success;
	double exeTime;

public:

	Test();
	virtual ~Test();

	void test_fight();
	void test_fight_v1();
	void test_generateCritical();
	void test_field();
	void test_line_of_sight();
	void test_pathfinding();
	void test_doc();

	void tests();
	void header(std::string);
	void add_weapons(FightManager& vm);
	void add_chips(FightManager& vm);
	void run_fight_browser(Report* report);

	template <typename T>
	void test(std::string message, T expected, T value);
};

#endif
