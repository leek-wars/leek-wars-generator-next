#include "../fight/Simulator.hpp"
#include "../fight/Fight.hpp"
#include "CellModule.hpp"
#include "EntityModule.hpp"
#include "../map/Map.hpp"
#include "../map/Cell.hpp"
#include "../entity/Entity.hpp"

const ls::LSClass* CellModule::cell_clazz;
const ls::Type CellModule::type(new CellType(), ls::Nature::POINTER, true);
const ls::Type CellModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, CellModule::type);

CellModule::CellModule() : Module("Cell") {

	CellModule::cell_clazz = this->clazz;

	field("x", ls::Type::NUMBER);
	field("y", ls::Type::NUMBER);
	field("id", ls::Type::NUMBER);
	field("entity", EntityModule::type_ptr);

	method("isEmpty", CellModule::type, ls::Type::BOOLEAN, {}, (void*) &Cell::isEmpty);
	method("hasEntity", CellModule::type, ls::Type::BOOLEAN, {}, (void*) &Cell::hasEntity);
	method("isObstacle", CellModule::type, ls::Type::BOOLEAN, {}, (void*) &Cell::isObstacle);
	method("distance", CellModule::type, ls::Type::INTEGER, {CellModule::type}, (void*) &Cell::distance);

	// v1 functions
	static_method("_isEmptyCell", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isEmptyCell);
	static_method("_isLeek", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isLeek);
	static_method("_isObstacle", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isObstacle);
	static_method("_getX", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &cell__getCellX);
	static_method("_getY", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &cell__getCellY);
	static_method("_getLeekOnCell", ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &cell__getLeekOnCell);
	static_method("_getCellContent", ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &cell__getCellContent);
}

CellModule::~CellModule() {}

/*
 * LS v1 support functions (deprecated in v2)
 */

/*
 * Always a bool
 */
bool cell__isEmptyCell(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return false;
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->isEmpty();
}

/*
 * Always a bool
 */
bool cell__isLeek(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return false;
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->hasEntity();
}

/*
 * Always a bool
 */
bool cell__isObstacle(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return false;
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->isObstacle();
}

/*
 * Null if the cell is invalid, int otherwise
 */
ls::LSValue* cell__getCellX(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return ls::LSNull::get();
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(c->x);
}

/*
 * Null if the cell is invalid, int otherwise
 */
ls::LSValue* cell__getCellY(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return ls::LSNull::get();
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(c->y);
}

/*
 * -1 if there's no entity, its ID otherwise, always an int
 */
int cell__getLeekOnCell(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return -1;
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return -1;

	if (c->entity != nullptr) {
		return c->entity->id;
	}
	return -1;
}

/*
 * -1 if invalid, 0, 1, 2 otherwise, always an int
 */
int cell__getCellContent(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return -1;
	const Cell* c = Simulator::fight->map->int_to_cell(n->value);
	if (c == nullptr) return -1;

	return c->getContent();
}
