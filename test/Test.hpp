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
#include "../src/colors.h"

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
	void test_censor();
	void test_generateCritical();
	void test_field();
	void test_doc();

	void tests();
	void header(std::string);
	void add_weapons(FightManager& vm);
	void add_chips(FightManager& vm);
	void run_fight_browser(Report* report);

	template <typename T>
	void test(std::string code, T expected, T res) {
		total++;
		if (expected != res) {
			std::cout << RED << "FAUX" << END_COLOR << " : " << code << "  =/=>  " << expected << "  got  " << res << std::endl;
		} else {
			std::cout << GREEN << "OK" << END_COLOR << "   : " << code << "  ===>  " << res << std::endl;
			success++;
		}
	}
	void test_ai(Fight* fight, Entity* entity, std::string code, std::string expected);
};

#endif
