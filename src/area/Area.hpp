#ifndef SRC_AREA_AREA_HPP_
#define SRC_AREA_AREA_HPP_

#include <vector>
#include "../effect/Attack.hpp"

enum class AreaType {
	SINGLE_CELL = 1,
	LASER_LINE = 2,
	CIRCLE1 = 3,
	CIRCLE2 = 4,
	CIRCLE3 = 5
};

class Area {
public:

	int id;
	Attack* attack;

	Area(Attack* attack);
	virtual ~Area();

	virtual std::vector<Cell*> getArea(Cell* launch, Cell* target) const = 0;

	bool isAvailable(Cell* c, std::vector<Cell*> ignored_cells);

	virtual int getRadius() const = 0;

	static Area* get(Attack* attack, AreaType type);
};

#endif
