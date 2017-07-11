#include <iterator>
#include <algorithm>
#include "Area.hpp"
#include "AreaSingleCell.hpp"
#include "AreaCircle.hpp"
#include "AreaLaserLine.hpp"
#include "../field/Cell.hpp"

Area::Area(Attack* attack) {
	this->id = -1;
	this->attack = attack;
}

Area::~Area() {}

bool Area::isAvailable(Cell* c, std::vector<Cell*> ignored_cells) {
	if (c->walkable) {
		return true;
	}
	if (ignored_cells.empty()) {
		return false;
	}
	return std::find(ignored_cells.begin(), ignored_cells.end(), c) != ignored_cells.end();
}

Area* Area::get(Attack* attack, AreaType type) {
	if (type == AreaType::SINGLE_CELL)
		return new AreaSingleCell(attack);
	else if (type == AreaType::LASER_LINE)
		return new AreaLaserLine(attack);
	else if (type == AreaType::CIRCLE1)
		return new AreaCircle(attack, 1);
	else if (type == AreaType::CIRCLE2)
		return new AreaCircle(attack, 2);
	else if (type == AreaType::CIRCLE3)
		return new AreaCircle(attack, 3);

	return nullptr;
}
