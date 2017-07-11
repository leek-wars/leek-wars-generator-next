#include <iostream>
#include "Cell.hpp"
#include "Map.hpp"
#include "../entity/Entity.hpp"

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
	this->values["x"] = ls::LSNumber::get(this->x);
	this->values["x"]->native = true;
	this->values["x"]->refs = 1;
	this->values["y"] = ls::LSNumber::get(this->y);
	this->values["y"]->native = true;
	this->values["y"]->refs = 1;
	this->values["obstacle"] = ls::LSBoolean::get(false);
	this->values["walkable"] = ls::LSBoolean::get(true);
	this->values["empty"] = ls::LSBoolean::get(true);
	this->values["entity"] = ls::LSNull::get();

	this->refs = 1;
	this->native = true;
	this->readonly = true;
}

Cell::~Cell() {
	delete values["id"];
	delete values["x"];
	delete values["y"];
	values.clear();
}

void Cell::setObstacle(int id, int size) {
	walkable = false;
	obstacle = id;
	obstacle_size = size;
	this->values["obstacle"] = ls::LSBoolean::get(true);
	this->values["walkable"] = ls::LSBoolean::get(false);
	this->values["empty"] = ls::LSBoolean::get(false);
}

void Cell::setEntity(Entity* entity) {
	if (this->entity == entity) {
		return;
	}
	if (entity == nullptr) {
		this->entity = nullptr;
		this->values["empty"] = ls::LSBoolean::get(walkable);
		this->values["entity"] = ls::LSNull::get();
		return;
	}
	entity->setCell(this);
	this->entity = entity;
	this->values["empty"] = ls::LSBoolean::get(false);
	this->values["entity"] = entity;
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
bool Cell::isWalkable() const {
	return walkable;
}

bool Cell::hasEntity() const {
	return entity != nullptr;
}

int Cell::getContent() const {
	return !walkable ? 2 : (entity != nullptr ? 1 : 0);
}

bool Cell::isAligned(const Cell* cell) const {
	return x == cell->x or y == cell->y;
}

Entity* Cell::getEntity() const {
	return entity == nullptr ? (Entity*)ls::LSNull::get() : entity;
}

int Cell::getX() const {
	return x;
}
int Cell::getY() const {
	return y;
}

ls::LSValue* Cell::getClass() const {
	return (LSValue*) CellModule::cell_clazz;
}

std::ostream& Cell::print(std::ostream& os) const {
	os << "<Cell " << id << ">";
	return os;
}
std::ostream& Cell::dump(std::ostream& os, int level) const {
	os << "<Cell " << id << ">";
	return os;
}

std::ostream& operator << (std::ostream& os, const Cell* cell) {
	os << "[" << cell->x << ", " << cell->y << "]";
	return os;
}
