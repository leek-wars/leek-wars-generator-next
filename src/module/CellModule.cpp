#include "../fight/Simulator.hpp"
#include "../fight/Fight.hpp"
#include "CellModule.hpp"
#include "EntityModule.hpp"
#include "../field/Field.hpp"
#include "../field/Cell.hpp"
#include "../entity/Entity.hpp"

const ls::LSClass* CellModule::cell_clazz;
const ls::Type CellModule::type(new CellType(), ls::Nature::POINTER, true);
const ls::Type CellModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, CellModule::type);

CellModule::CellModule() : Module("Cell") {

	CellModule::cell_clazz = this->clazz;

	field("x", ls::Type::NUMBER);
	field("y", ls::Type::NUMBER);
	field("id", ls::Type::NUMBER);
	field("entity", EntityModule::type);
	field("obstacle", ls::Type::BOOLEAN_P);
	field("walkable", ls::Type::BOOLEAN_P);
	field("empty", ls::Type::BOOLEAN_P);

	method("isEmpty", {{ls::Type::BOOLEAN, {CellModule::type}, (void*) &Cell::isEmpty, ls::Method::NATIVE}});
	method("hasEntity", {{ls::Type::BOOLEAN, {CellModule::type}, (void*) &Cell::hasEntity, ls::Method::NATIVE}});
	method("isObstacle", {{ls::Type::BOOLEAN, {CellModule::type}, (void*) &Cell::isObstacle, ls::Method::NATIVE}});
	method("isWalkable", {{ls::Type::BOOLEAN, {CellModule::type}, (void*) &Cell::isWalkable, ls::Method::NATIVE}});
	method("distance", {{ls::Type::INTEGER, {CellModule::type, CellModule::type}, (void*) &Cell::distance, ls::Method::NATIVE}});
	method("getX", {{ls::Type::INTEGER, {CellModule::type}, (void*) &Cell::getX, ls::Method::NATIVE}});
	method("getY", {{ls::Type::INTEGER, {CellModule::type}, (void*) &Cell::getY, ls::Method::NATIVE}});
	method("getEntity", {{EntityModule::type, {CellModule::type}, (void*) &Cell::getEntity, ls::Method::NATIVE}});
	method("isAligned", {{ls::Type::BOOLEAN, {CellModule::type, CellModule::type}, (void*) &Cell::isAligned, ls::Method::NATIVE}});

	// v1 functions
	method("_isEmptyCell", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isEmptyCell}});
	method("_isLeek", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isLeek}});
	method("_isObstacle", {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &cell__isObstacle}});
	method("_getX", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &cell__getCellX}});
	method("_getY", {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &cell__getCellY}});
	method("_getLeekOnCell", {{ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &cell__getLeekOnCell}});
	method("_getCellContent", {{ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &cell__getCellContent}});
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
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->isEmpty();
}

/*
 * Always a bool
 */
bool cell__isLeek(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return false;
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->hasEntity();
}

/*
 * Always a bool
 */
bool cell__isObstacle(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return false;
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return false;

	return c->isObstacle();
}

/*
 * Null if the cell is invalid, int otherwise
 */
ls::LSValue* cell__getCellX(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return ls::LSNull::get();
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(c->x);
}

/*
 * Null if the cell is invalid, int otherwise
 */
ls::LSValue* cell__getCellY(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return ls::LSNull::get();
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(c->y);
}

/*
 * -1 if there's no entity, its ID otherwise, always an int
 */
int cell__getLeekOnCell(const ls::LSValue* cell) {

	const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(cell);
	if (n == nullptr) return -1;
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
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
	const Cell* c = Simulator::fight->field->int_to_cell(n->value);
	if (c == nullptr) return -1;

	return c->getContent();
}
