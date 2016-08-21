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
	virtual ~Color();

	ls::LSValue* attr(const ls::LSValue* key) const override;

	std::ostream& print(std::ostream& os) const;
};

#endif /* SRC_UTIL_COLOR_HPP_ */
