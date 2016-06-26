/*
 * ColorModule.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#ifndef SRC_MODULE_COLORMODULE_HPP_
#define SRC_MODULE_COLORMODULE_HPP_

#include <leekscript.h>

#include "../util/Color.hpp"
#include "CellModule.hpp"

class ColorType : public ls::IntegerRawType {
public:
	const std::string getName() const { return "Color"; };
};

class ColorModule : public ls::Module {
public:
	ColorModule();
	virtual ~ColorModule();

	static const ls::LSClass* color_clazz;
	static const ColorType* const type;
	static const ls::Type type_ptr;
};

#endif

Color* color_rgb(ls::LSNumber* r, ls::LSNumber* g, ls::LSNumber* b);
Color* color_rgba(ls::LSNumber* r, ls::LSNumber* g, ls::LSNumber* b, ls::LSNumber* a);
