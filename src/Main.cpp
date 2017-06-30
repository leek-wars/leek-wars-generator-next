#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <leekscript/src/leekscript.h>

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
#include "fight/FightLoader.hpp"
#include "fight/FightManager.hpp"

using namespace std;

int main(int argc, char** argv) {

	cout << "~~ leek-wars-simulator v1.0 ~~" << endl;

	// Global initialization
	srand(time(NULL));
	auto null_value = ls::LSNull::create();
	auto true_value = ls::LSBoolean::create(true);
	auto false_value = ls::LSBoolean::create(false);
	ls::LSNull::set_null_value(null_value);
	ls::LSBoolean::set_true_value(true_value);
	ls::LSBoolean::set_false_value(false_value);

	// Load a fight file?
	if (argc == 2) {
		std::string fight_file(argv[1]);
		std::cout << "load fight '" << fight_file << "'..." << std::endl;
		auto fight = FightLoader::load(fight_file);
		auto report = FightManager().start(*fight);
		std::cout << report << std::endl;
		delete report;
		return 0;
	}


	return 0;
}
