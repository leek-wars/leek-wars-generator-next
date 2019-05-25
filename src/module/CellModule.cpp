#include "../fight/Simulator.hpp"
#include "../fight/Fight.hpp"
#include "CellModule.hpp"
#include "EntityModule.hpp"
#include "../field/Field.hpp"
#include "../field/Cell.hpp"
#include "../entity/Entity.hpp"

const ls::LSClass* CellModule::cell_clazz;
const std::shared_ptr<CellType> CellModule::raw_type = std::make_shared<CellType>();
const ls::Type CellModule::type(raw_type, true);
const ls::Type CellModule::const_type(raw_type, true, false, true);
const ls::Type CellModule::array_type = ls::Type::array(CellModule::type);

CellModule::CellModule() : Module("Cell") {

	CellModule::cell_clazz = this->clazz;

	field("x", ls::Type::integer(), (void*) &Cell::getX);
	field("y", ls::Type::integer(), (void*) &Cell::getY);
	field("id", ls::Type::integer(), (void*) &Cell::getId);
	field("entity", EntityModule::type, (void*) &Cell::getEntity);
	field("obstacle", ls::Type::boolean(), (void*) &Cell::isObstacle);
	field("walkable", ls::Type::boolean(), (void*) &Cell::isWalkable);
	field("empty", ls::Type::boolean(), (void*) &Cell::isEmpty);

	method("distance", {{ls::Type::integer(), {CellModule::type, CellModule::type}, (void*) &Cell::distance}});
	method("isAligned", {{ls::Type::boolean(), {CellModule::type, CellModule::type}, (void*) &Cell::isAligned}});

	// v1 functions
	method("isEmptyCell", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &cell__isEmptyCell}});
	method("isLeek", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &cell__isLeek}});
	method("isObstacle", {{ls::Type::boolean(), {ls::Type::any()}, (void*) &cell__isObstacle}});
	method("getX", {{ls::Type::any(), {ls::Type::any()}, (void*) &cell__getCellX}});
	method("getY", {{ls::Type::any(), {ls::Type::any()}, (void*) &cell__getCellY}});
	method("getLeekOnCell", {{ls::Type::integer(), {ls::Type::any()}, (void*) &cell__getLeekOnCell}});
	method("getCellContent", {{ls::Type::integer(), {ls::Type::any()}, (void*) &cell__getCellContent}});
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
