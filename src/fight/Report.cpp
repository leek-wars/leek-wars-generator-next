#include <iostream>
#include "Report.hpp"
#include "Fight.hpp"
#include "../map/Map.hpp"

using namespace std;

Report::Report(Fight* fight) : fight(fight) {
	actions = nullptr;
}

Report::~Report() {}

std::ostream& operator << (std::ostream& os, const Report* report) {

	Json json = {
		{"actions", report->actions->json()},
		{"map", report->fight->map->json()}
	};

	os << json;

	return os;
}
