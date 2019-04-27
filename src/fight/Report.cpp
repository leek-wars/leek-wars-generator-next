#include <iostream>
#include "Report.hpp"
#include "Fight.hpp"
#include "../field/Field.hpp"

Report::Report(Fight* fight) : fight(fight) {
	actions = nullptr;
}

Report::~Report() {}

std::ostream& operator << (std::ostream& os, const Report* report) {

	Json json = {{"fight", 
		{
			{"actions", report->actions->json()},
			{"map", report->fight->field->json()},
			{"leeks", report->fight->entities_json()},
			{"logs", report->fight->actions.logs}
		}
	}};

	os << json;

	return os;
}
