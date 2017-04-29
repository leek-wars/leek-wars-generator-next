#include <iomanip>
#include "Color.hpp"

Color::Color() : Color(0) {}

Color::Color(int color, bool native) : LSNumber(color) {
	this->native = native;
	refs = 1;
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

ls::LSValue* Color::clone() const {
	if (native) return (ls::LSValue*) this;
	return new Color(value, false);
}

std::ostream& Color::print(std::ostream& os) const {
	os << "#" << std::hex << std::setfill('0') << std::setw(8) << (unsigned int) value << std::dec;
	return os;
}
