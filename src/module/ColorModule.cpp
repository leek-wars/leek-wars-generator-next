/*
 * ColorModule.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#include "ColorModule.hpp"

const ls::LSClass* ColorModule::color_clazz;
const ColorType* const ColorModule::type = new ColorType();
const ls::Type ColorModule::type_ptr(ColorModule::type, ls::Nature::POINTER);

ColorModule::ColorModule() : Module("Color") {

	static_field("BLACK", ColorModule::type_ptr, nullptr);

	field("r", Type::INTEGER_P);
	field("g", Type::INTEGER_P);
	field("b", Type::INTEGER_P);

	static_method("rgb", ColorModule::type_ptr, {Type::INTEGER_P, Type::INTEGER_P, Type::INTEGER_P}, (void*) &color_rgb);
	static_method("rgba", ColorModule::type_ptr, {Type::INTEGER_P, Type::INTEGER_P, Type::INTEGER_P, Type::INTEGER_P}, (void*) &color_rgba);

	ColorModule::color_clazz = this->clazz;
}

ColorModule::~ColorModule() {

}

Color* color_rgb(ls::LSNumber* r, ls::LSNumber* g, ls::LSNumber* b) {

	Color* color = new Color();

	unsigned int red = (((int) r->value) << 16) & 0x00FF0000;
	unsigned int green = (((int) g->value) << 8) & 0x0000FF00;
	unsigned int blue = ((int) b->value) & 0x000000FF;

	color->value = 0xFF000000 | red | green | blue;
	return color;
}

Color* color_rgba(ls::LSNumber* r, ls::LSNumber* g, ls::LSNumber* b, ls::LSNumber* a) {

	Color* color = new Color();

	unsigned int alpha = (((int) a->value) << 24) & 0xFF000000;
	unsigned int red = (((int) r->value) << 16) & 0x00FF0000;
	unsigned int green = (((int) g->value) << 8) & 0x0000FF00;
	unsigned int blue = ((int) b->value) & 0x000000FF;

	color->value = alpha | red | green | blue;
	return color;
}
