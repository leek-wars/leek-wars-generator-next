#include <iostream>
#include "Cell.hpp"
#include "Field.hpp"
#include "../entity/Entity.hpp"

Cell::Cell(Field* field, int id, int x, int y) {

	this->id = id;
	this->field = field;
	this->walkable = true;
	this->obstacle = 0;
	this->entity = nullptr;
	this->obstacle_size = 0;
	this->x = x;
	this->y = y;

	if (x + y == field->width - 1) east = south = false;
	if (-x - y == field->width - 1) north = west = false;
	if (x - y == field->width - 1) north = east = false;
	if (-x + y == field->width - 1) west = south = false;

	this->refs = 1;
	this->native = true;
	this->readonly = true;
}

Cell::~Cell() {}

void Cell::setObstacle(int id, int size) {
	walkable = false;
	obstacle = id;
	obstacle_size = size;
}

void Cell::setEntity(Entity* entity) {
	if (this->entity == entity) {
		return;
	}
	if (entity == nullptr) {
		this->entity = nullptr;
		return;
	}
	entity->setCell(this);
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
int Cell::getId() const {
	return id;
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
