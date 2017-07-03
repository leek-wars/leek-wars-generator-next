#include "Pathfinding.hpp"
#include "Map.hpp"

Cell* Pathfinding::getCellByDir(Cell* cell, Direction dir) {

	if (cell == nullptr) {
		return nullptr;
	}
	if (dir == Direction::NORTH and cell->north) {
		return (Cell*) cell->map->int_to_cell(cell->id - cell->map->width + 1);
	} else if (dir == Direction::WEST && cell->west) {
		return (Cell*) cell->map->int_to_cell(cell->id - cell->map->width);
	} else if (dir == Direction::EAST && cell->east) {
		return (Cell*) cell->map->int_to_cell(cell->id + cell->map->width);
	} else if (dir == Direction::SOUTH && cell->south) {
		return (Cell*) cell->map->int_to_cell(cell->id + cell->map->width - 1);
	}
	return nullptr;
}
