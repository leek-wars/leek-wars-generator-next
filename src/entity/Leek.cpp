#include "Leek.hpp"
#include "../module/LeekModule.hpp"

Leek::Leek(Fight* fight, std::string name, int level, AI* ai, int skin, int hat)
	: Entity(fight, name, level), skin(skin), hat(hat) {
	this->ai.reset(ai);
	addField("farmerID", new ls::LSNumber(1212));
	addField("farmerName", new ls::LSString("Toto"));
}

Leek::~Leek() {}
