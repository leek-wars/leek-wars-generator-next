#include "AreaCircle.hpp"
#include "AreaMask.hpp"
#include "../field/Cell.hpp"
#include "../field/Field.hpp"

std::map<int, std::vector<std::pair<int, int>>> AreaCircle::area_cache;

AreaCircle::AreaCircle(Attack* attack, int radius) : Area(attack) {
	this->radius = radius;
	area_cache[radius] = AreaMask::generateCircleMask(0, radius);
}

AreaCircle::~AreaCircle() {}

std::vector<Cell*> AreaCircle::getArea(Cell* launchCell, Cell* targetCell) const {

	int x = targetCell->x;
	int y = targetCell->y;
	std::vector<Cell*> cells;
	auto area = area_cache[radius];
	auto field = launchCell->field;

	for (std::pair<int, int> v : area) {
		auto c = field->get_cell(x + v.first, y + v.second);
		if (c == nullptr || !c->walkable) {
			continue;
		}
		cells.push_back(c);
	}
	return cells;
}

int AreaCircle::getRadius() const {
	return 2;
}
