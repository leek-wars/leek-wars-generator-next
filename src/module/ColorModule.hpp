#ifndef SRC_MODULE_COLORMODULE_HPP_
#define SRC_MODULE_COLORMODULE_HPP_

#include <leekscript.h>
#include "../util/Color.hpp"
#include "CellModule.hpp"

class ColorType : public ls::Integer_type {
public:
	virtual const std::string getName() const override { return "color"; };
	virtual std::string clazz() const override { return "Color"; };
};

class ColorModule : public ls::Module {
public:
	ColorModule();
	virtual ~ColorModule();

	static const ls::LSClass* color_clazz;
	static const std::shared_ptr<ColorType> type;
	static const ls::Type type_ptr;

	static const Color* TRANSPARENT;
	static const Color* BLACK;
	static const Color* WHITE;
	static const Color* RED;
	static const Color* GREEN;
	static const Color* BLUE;
};

#endif
