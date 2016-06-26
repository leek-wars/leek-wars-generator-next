/*
 * Report.hpp
 *
 *  Created on: 31 mars 2016
 *      Author: pierre
 */

#ifndef REPORT_HPP_
#define REPORT_HPP_

#include "../action/Actions.hpp"
#include <ostream>

class Report {
public:

	Actions* actions;

	Report();
	virtual ~Report();

	friend std::ostream& operator << (std::ostream& os, const Report* map);
};

#endif
