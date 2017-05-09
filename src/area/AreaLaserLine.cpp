#include "AreaLaserLine.hpp"

AreaLaserLine::AreaLaserLine(Attack* attack) : Area(attack) {}

AreaLaserLine::~AreaLaserLine() {}

std::vector<Cell*> AreaLaserLine::getArea(Cell*, Cell*) const {
	return {};
}

int AreaLaserLine::getRadius() const {
	return 0;
}
