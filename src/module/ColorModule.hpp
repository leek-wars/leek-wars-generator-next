#ifndef SRC_MODULE_COLORMODULE_HPP_
#define SRC_MODULE_COLORMODULE_HPP_

#include <leekscript.h>
#include "../util/Color.hpp"
#include "CellModule.hpp"

class ColorType : public ls::Integer_type {
public:
	virtual const std::string getName() const override { return "color"; };
	virtual std::string class_name() const override { return "Color"; };
	virtual Type* clone() const override { return new ColorType(); }
};

class ColorModule : public ls::Module {
public:
	ColorModule(ls::VM* vm);
	virtual ~ColorModule();

	static const ls::LSClass* color_clazz;
	static const std::shared_ptr<ColorType> raw_type;
	static const ls::Type* type;

	static const Color* TRANSPARENT;
	static const Color* BLACK;
	static const Color* WHITE;
	static const Color* RED;
	static const Color* GREEN;
	static const Color* BLUE;
};

#endif
