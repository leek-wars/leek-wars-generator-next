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

int main(int argc, char** argv) {

	LOG << "~~ leek-wars-simulator v1.0 ~~" << endl;

	// Load a fight file?
	if (argc < 2) {
		std::cout << "Missing fight input!" << std::endl << "Usage: leek-wars-generator fight.json" << std::endl;
		return 1;
	}

	// Global initialization
	srand(time(NULL));
	ls::LSNull::set_null_value(ls::LSNull::create());
	ls::LSBoolean::set_true_value(ls::LSBoolean::create(true));
	ls::LSBoolean::set_false_value(ls::LSBoolean::create(false));

	// Start the fight
	std::string fight_file(argv[1]);
 	LOG << "Load fight '" << fight_file << "'..." << std::endl;
	auto fight = FightLoader::load(fight_file);

	FightManager().start(*fight, [](Report* report) {
		// Display the report
		std::cout << report << std::endl;
		// Start a browser with the fight
		std::ofstream report_file("fight.json");
		report_file << report << std::endl;
		// system("chromium-browser http://localhost:8012/fight/local");
		delete report;
		exit(0);
	});
	return 0;
}
