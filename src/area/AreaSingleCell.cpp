#include "AreaSingleCell.hpp"

AreaSingleCell::AreaSingleCell(Attack* attack) : Area(attack) {}

AreaSingleCell::~AreaSingleCell() {}

std::vector<Cell*> AreaSingleCell::getArea(Cell*, Cell* target) const {
	return { target };
}

int AreaSingleCell::getRadius() const {
	return 0;
}
