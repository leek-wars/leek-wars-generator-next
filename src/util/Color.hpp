/*
 * Color.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#ifndef SRC_UTIL_COLOR_HPP_
#define SRC_UTIL_COLOR_HPP_

#include <leekscript/src/leekscript.h>

class Color : public ls::LSNumber {
public:
	Color();
	Color(int color, bool native = false);
	virtual ~Color();

	ls::LSValue* attr(const std::string& key) const override;
	ls::LSValue* clone() const override;
	std::ostream& print(std::ostream& os) const;
};

#endif
