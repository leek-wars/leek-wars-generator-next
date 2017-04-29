/*
 * Color.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#include <iomanip>
#include "Color.hpp"

Color::Color() : Color(0) {}

Color::Color(int color, bool native) : LSNumber(0) {
	this->value = color;
	this->native = native;
}

Color::~Color() {}

ls::LSValue* Color::attr(const std::string& k) const {
	if (k == "r") {
		return ls::LSNumber::get((((unsigned int) value) & 0xFF0000) >> 16);
	} else if (k == "g") {
		return ls::LSNumber::get((((unsigned int) value) & 0x00FF00) >> 8);
	} else if (k == "b") {
		return ls::LSNumber::get(((unsigned int) value) & 0x0000FF);
	} else if (k == "a") {
		return ls::LSNumber::get((((unsigned int) value) & 0xFF000000) >> 24);
	}
	return ls::LSNull::get();
}

std::ostream& Color::print(std::ostream& os) const {

	os << "#" << std::hex << std::setfill('0') << std::setw(8) << (unsigned int) value << std::dec;
	return os;
}
