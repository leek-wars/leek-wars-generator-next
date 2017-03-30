#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <string>
#include <chrono>

#include "../src/fight/Fight.hpp"
#include "../src/entity/Leek.hpp"
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

class Test {

	int total;
	int success;
	double exeTime;

public:

	Test();
	virtual ~Test();

	void test_fight();
	void test_generateCritical();
	void test_map();

	void tests();
	void header(std::string);

	template <typename T>
	void test(std::string message, T expected, T value);
};

#endif
