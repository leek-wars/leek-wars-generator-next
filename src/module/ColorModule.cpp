#include "ColorModule.hpp"

const ls::LSClass* ColorModule::color_clazz;
const ColorType* const ColorModule::type = new ColorType();
const ls::Type ColorModule::type_ptr(ColorModule::type, ls::Nature::POINTER);

const Color* ColorModule::TRANSPARENT = new Color(0x00000000, true);
const Color* ColorModule::BLACK = new Color(0xff000000, true);
const Color* ColorModule::WHITE = new Color(0xffffffff, true);
const Color* ColorModule::RED = new Color(0xffff0000, true);
const Color* ColorModule::GREEN = new Color(0xff00ff00, true);
const Color* ColorModule::BLUE = new Color(0xff0000ff, true);

Color* color_rgb(int r, int g, int b) {
	auto color = new Color();
	color->value = ((255 & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return color;
}

Color* color_rgba(int r, int g, int b, int a) {
	auto color = new Color();
	color->value = ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return color;
}

ColorModule::ColorModule() : Module("Color") {

	static_field("TRANSPARENT", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::TRANSPARENT); });
	static_field("BLACK", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::BLACK); });
	static_field("WHITE", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::WHITE); });
	static_field("RED", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::RED); });
	static_field("GREEN", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::GREEN); });
	static_field("BLUE", ColorModule::type_ptr, [](ls::Compiler& c) { return c.new_pointer((void*) ColorModule::BLUE); });

	field("r", ls::Type::NUMBER);
	field("g", ls::Type::NUMBER);
	field("b", ls::Type::NUMBER);
	field("a", ls::Type::NUMBER);

	static_method("rgb", {
		{ColorModule::type_ptr, {ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER}, (void*) &color_rgb, ls::Method::NATIVE}
	});
	static_method("rgba", {
		{ColorModule::type_ptr, {ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER}, (void*) &color_rgba, ls::Method::NATIVE}
	});

	ColorModule::color_clazz = this->clazz;
}

ColorModule::~ColorModule() {}
