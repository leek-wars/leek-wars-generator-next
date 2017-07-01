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

	// Read options
	bool quiet = false;
	bool compile = false;
	std::string input;
	for (int i = 1; i < argc; ++i) {
		std::string o(argv[i]);
		if (o == "-q" or o == "-Q") quiet = true;
		else if (o == "-c" or o == "-C") compile = true;
		else input = o;
	}
	if (not input.size()) {
		std::cout << "Missing input!" << std::endl << "Usage: leek-wars-generator [options] input" << std::endl;
		return 1;
	}

	if (quiet) {
		Util::log_enabled = false;
	}

	LOG << "~~ leek-wars-simulator v1.0 ~~" << endl;

	if (compile) {
		auto res = FightManager().compile(input);
		std::cout << res << std::endl;
		return 0;
	}

	// Global initialization
	srand(time(NULL));
	ls::LSNull::set_null_value(ls::LSNull::create());
	ls::LSBoolean::set_true_value(ls::LSBoolean::create(true));
	ls::LSBoolean::set_false_value(ls::LSBoolean::create(false));

	// Start the fight
	std::string fight_file(argv[2]);
 	LOG << "Load fight '" << fight_file << "'..." << std::endl;
	auto fight = FightLoader::load(fight_file);
	if (fight == nullptr) {
		LOG_W << "Fight failed to load!" << std::endl;
		return 0;
	}

	FightManager().start(*fight, [](Report* report) {
		LOG_I << "Fight generated!" << std::endl;
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
