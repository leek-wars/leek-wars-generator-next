/*
 * Color.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#include <iomanip>
#include "Color.hpp"

Color::Color() {

}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

ls::LSValue* Color::attr(const ls::LSValue* key) const {
	std::string k = *((ls::LSString*) key);
	if (k == "r") {
		return ls::LSNumber::get((((unsigned int) value) & 0xFF0000) >> 16);
	}
	else if (k == "g") {
		return ls::LSNumber::get((((unsigned int) value) & 0x00FF00) >> 8);
	}
	else if (k == "b") {
		return ls::LSNumber::get(((unsigned int) value) & 0x0000FF);
	}
	return ls::LSNull::null_var;
}

std::ostream& Color::print(std::ostream& os) const {

	os << "#" << std::hex << std::setfill('0') << std::setw(8) << (unsigned int) value;
	return os;
}
