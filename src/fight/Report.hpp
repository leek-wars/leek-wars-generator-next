#ifndef REPORT_HPP_
#define REPORT_HPP_

#include "../action/Actions.hpp"
class Fight;
#include <ostream>

class Report {
public:

	Fight* fight;
	Actions* actions;

	Report(Fight* fight);
	virtual ~Report();

	friend std::ostream& operator << (std::ostream& os, const Report* map);
};

#endif
