#include "Leek.hpp"

#include "../module/LeekModule.hpp"

Leek::Leek(Fight* fight, std::string name, int level, AI* ai)
	: Entity(fight, name, level) {

	this->ai = ai;
	addField("farmerID", new ls::LSNumber(1212));
	addField("farmerName", new ls::LSString("Toto"));
}

Leek::~Leek() {}
