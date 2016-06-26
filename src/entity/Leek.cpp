#include "Leek.hpp"

#include "../module/LeekModule.hpp"

Leek::Leek(Fight* fight, std::string name, int level, AI* ai)
	: Entity(fight, name, level) {

	this->ai = ai;
	values["farmerID"] = new ls::LSNumber(1212);
	values["farmerName"] = new ls::LSString("Toto");
}

Leek::~Leek() {}

