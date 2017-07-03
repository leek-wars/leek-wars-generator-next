#include <iostream>
#include "Report.hpp"
#include "Fight.hpp"
#include "../map/Map.hpp"

Report::Report(Fight* fight) : fight(fight) {
	actions = nullptr;
}

Report::~Report() {}

std::ostream& operator << (std::ostream& os, const Report* report) {

	Json json = {
		{"actions", report->actions->json()},
		{"map", report->fight->map->json()},
		{"leeks", report->fight->entities_json()},
		{"logs", report->fight->actions.logs}
	};

	os << json;

	return os;
}
