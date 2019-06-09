#include "ColorModule.hpp"

const ls::LSClass* ColorModule::color_clazz;
const std::shared_ptr<ColorType> ColorModule::raw_type = std::make_shared<ColorType>();
const ls::Type* ColorModule::type = new ls::Type(ColorModule::raw_type);

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

ColorModule::ColorModule(ls::VM* vm) : Module(vm, "Color") {

	static_field("TRANSPARENT", ColorModule::type, &ColorModule::TRANSPARENT);
	static_field("BLACK", ColorModule::type, &ColorModule::BLACK);
	static_field("WHITE", ColorModule::type, &ColorModule::WHITE);
	static_field("RED", ColorModule::type, &ColorModule::RED);
	static_field("GREEN", ColorModule::type, &ColorModule::GREEN);
	static_field("BLUE", ColorModule::type, & ColorModule::BLUE);

	field("r", ls::Type::number);
	field("g", ls::Type::number);
	field("b", ls::Type::number);
	field("a", ls::Type::number);

	method("rgb", {
		{ColorModule::type, {ls::Type::integer, ls::Type::integer, ls::Type::integer}, (void*) &color_rgb}
	});
	method("rgba", {
		{ColorModule::type, {ls::Type::integer, ls::Type::integer, ls::Type::integer, ls::Type::integer}, (void*) &color_rgba}
	});

	ColorModule::color_clazz = this->clazz;
}

ColorModule::~ColorModule() {}
