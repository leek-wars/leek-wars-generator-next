/*
 * AreaSingleCell.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#include "AreaSingleCell.hpp"

AreaSingleCell::AreaSingleCell(Attack* attack) : Area(attack) {}

AreaSingleCell::~AreaSingleCell() {}

std::vector<Cell*> AreaSingleCell::getArea(Cell* launch, Cell* target) const {
	return std::vector<Cell*> { target };
}

int AreaSingleCell::getRadius() const {
	return 0;
}
