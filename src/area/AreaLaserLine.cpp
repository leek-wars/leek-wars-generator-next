#include "AreaLaserLine.hpp"
#include "../field/Cell.hpp"
#include "../field/Field.hpp"

AreaLaserLine::AreaLaserLine(Attack* attack) : Area(attack) {}

AreaLaserLine::~AreaLaserLine() {}

std::vector<Cell*> AreaLaserLine::getArea(Cell* launch_cell, Cell* target_cell) const {
	std::vector<Cell*> cells;
	int dx = 0, dy = 0;
	if (launch_cell->x == target_cell->x) {
		if (launch_cell->y > target_cell->y) {
			dy = -1;
		} else {
			dy = 1;
		}
	} else if (launch_cell->y == target_cell->y) {
		if (launch_cell->x > target_cell->x) {
			dx = -1;
		} else {
			dx = 1;
		}
	} else {
		return cells;
	}
	int x = launch_cell->x, y = launch_cell->y;
	for (int i = attack->min_range; i <= attack->max_range; i++) {
		auto* c = launch_cell->field->get_cell(x + dx * i, y + dy * i);
		if (c == nullptr or !c->walkable) {
			break;
		}
		cells.push_back(c);
	}
	return cells;
}

int AreaLaserLine::getRadius() const {
	return 0;
}
