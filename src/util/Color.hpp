#ifndef SRC_UTIL_COLOR_HPP_
#define SRC_UTIL_COLOR_HPP_

#include <leekscript.h>

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
