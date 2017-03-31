#include <iostream>
#include "Cell.hpp"
#include "Map.hpp"
#include "../entity/Entity.hpp"

using namespace std;

Cell::Cell(Map* map, int id) {

	this->id = id;
	this->map = map;
	this->walkable = true;
	this->obstacle = 0;
	this->entity = nullptr;
	this->obstacle_size = 0;

	int x = id % (map->width * 2 - 1);
	int y = id / (map->width * 2 - 1);
	if (y == 0 && x < map->width) {
		north = false;
		west = false;
	} else if (y + 1 == map->height && x >= map->width) {
		east = false;
		south = false;
	}
	if (x == 0) {
		south = false;
		west = false;
	} else if (x + 1 == map->width) {
		north = false;
		east = false;
	}

	this->y = y - x % map->width;
	this->x = (id - (map->width - 1) * this->y) / map->width;

	this->values["id"] = ls::LSNumber::get(id);
	this->values["id"]->native = true;
	this->values["id"]->refs = 1;
	this->values["x"] = ls::LSNumber::get(x);
	this->values["x"]->native = true;
	this->values["x"]->refs = 1;
	this->values["y"] = ls::LSNumber::get(y);
	this->values["y"]->native = true;
	this->values["y"]->refs = 1;
	this->readonly = true;
}

Cell::~Cell() {
	delete this->values["id"];
	delete this->values["x"];
	delete this->values["y"];
}

void Cell::setObstacle(int id, int size) {
	walkable = false;
	obstacle = id;
	obstacle_size = size;
}

void Cell::setEntity(Entity* entity) {
	if (this->entity == entity) {
		return;
	}
	this->map->positionChanged();
	if (entity == nullptr) {
		this->entity = nullptr;
		return;
	}
	entity->cell = this;
	this->entity = entity;
}

bool Cell::available() const {
	return walkable && entity == nullptr;
}

bool Cell::available(Cell* cell) {
	// TODO lapin compris
	return walkable && (entity == nullptr || this == cell);
}

int Cell::distance(const Cell* cell2) const {
	return abs(x - cell2->x) + abs(y - cell2->y);
}

double Cell::straightDistance(const Cell* cell2) const {
	return sqrt((x - cell2->x) * (x - cell2->x) + (y - cell2->y) * (y - cell2->y));
}

bool Cell::isEmpty() const {
	return walkable && entity == nullptr;
}

bool Cell::isObstacle() const {
	return !walkable;
}

bool Cell::hasEntity() const {
	return entity != nullptr;
}

int Cell::getContent() const {
	return !walkable ? 2 : (entity != nullptr ? 1 : 0);
}

bool Cell::isOnSameLine(const Cell* cell) const {
	return x == cell->x or y == cell->y;
}

ls::LSValue* Cell::getClass() const {
	return (LSValue*) CellModule::cell_clazz;
}

std::ostream& Cell::print(std::ostream& os) const {
	os << "<Cell " << id << ">";
}

std::ostream& operator << (std::ostream& os, const Cell* cell) {
	os << "[" << cell->x << ", " << cell->y << "]";
	return os;
}
