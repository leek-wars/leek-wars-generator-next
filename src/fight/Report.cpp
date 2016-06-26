#include <iostream>
#include "Report.hpp"
using namespace std;

Report::Report() {}

Report::~Report() {}

std::ostream& operator << (std::ostream& os, const Report* report) {

	os << "{\"actions\":" << report->actions->json() << "}";

	return os;
}
