#include "ItemModule.hpp"

ItemModule::ItemModule() : Module("Item") {

	static_field("USE_SUCCESS", ls::Type::integer(), [](ls::Compiler& c) { return c.new_integer(1); });
}

ItemModule::~ItemModule() {}
