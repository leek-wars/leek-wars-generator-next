#include "Test.hpp"
#include <istream>
#include <fstream>
#include "../src/area/Area.hpp"
#include "../src/effect/Attack.hpp"

void Test::run_fight_browser(Report* report) {
	std::ofstream report_file("fight.json");
	report_file << report << std::endl;
	system("chromium-browser http://localhost:8012/fight/local");
}
