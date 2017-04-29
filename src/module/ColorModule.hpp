#ifndef SRC_MODULE_COLORMODULE_HPP_
#define SRC_MODULE_COLORMODULE_HPP_

#include <leekscript/src/leekscript.h>

#include "../util/Color.hpp"
#include "CellModule.hpp"

class ColorType : public ls::IntegerRawType {
public:
	const std::string getName() const { return "color"; };
	const std::string getClass() const { return "Color"; };
};

class ColorModule : public ls::Module {
public:
	ColorModule();
	virtual ~ColorModule();

	static const ls::LSClass* color_clazz;
	static const ColorType* const type;
	static const ls::Type type_ptr;

	static const Color* TRANSPARENT;
	static const Color* BLACK;
	static const Color* WHITE;
	static const Color* RED;
	static const Color* GREEN;
	static const Color* BLUE;
};

#endif
