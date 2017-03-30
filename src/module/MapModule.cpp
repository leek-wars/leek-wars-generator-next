#include "MapModule.hpp"

#include <vector>

#include "../fight/Simulator.hpp"
#include "../map/Map.hpp"
#include "../fight/Fight.hpp"
#include "../entity/Entity.hpp"

using namespace std;

MapModule::MapModule() : Module("FightMap") {

	static_method("cell", CellModule::type, {ls::Type::INTEGER, ls::Type::INTEGER}, (void*) &map_cell);
	static_method("lineOfSight", ls::Type::BOOLEAN, {CellModule::type, CellModule::type}, (void*) &map_lineOfSight);
	static_method("getPath", CellModule::array_type, {CellModule::type, CellModule::type}, (void*) &map_getPath);
	static_method("getPathLength", ls::Type::INTEGER, {CellModule::type, CellModule::type}, (void*) &map_getPathLength);
	static_method("getCellContent", ls::Type::INTEGER, {CellModule::type}, (void*) &map_getCellContent);
	static_method("getDistance", ls::Type::INTEGER, {CellModule::type, CellModule::type}, (void*) &map_getDistance);
	static_method("getStraightDistance", ls::Type::REAL, {CellModule::type}, (void*) &map_getStraightDistance);
	static_method("getType", ls::Type::INTEGER, {}, (void*) &map_getType);
	static_method("getObstacles", ls::Type::INTEGER, {}, (void*) &map_getObstacles);

	// v1 functions
	static_method("_getCellDistance", ls::Type::INTEGER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getCellDistance);
	static_method("_getCellFromXY", ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getCellFromXY);
	static_method("_getDistance", ls::Type::REAL, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getDistance);
	static_method("_getMapType", ls::Type::INTEGER, {}, (void*) &map__getMapType);
	static_method("_getObstacles", ls::Type::INT_ARRAY, {}, (void*) &map__getObstacles);
	static_method("_getPath", {
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getPath},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getPathIgnored}
	});
	static_method("_getPathLength", {
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getPathLength},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__getPathLengthIgnored}
	});
	static_method("_isOnSameLine", ls::Type::BOOLEAN, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__isOnSameLine);
	static_method("_lineOfSight", {
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__lineOfSight},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &map__lineOfSightIgnored}
	});
}

MapModule::~MapModule() {}


const Cell* map_cell(const int x, const int y) {
	// TODO check null cell
	return Simulator::fight->map->getCell(x, y);
}

int map_getCellContent(const Cell* cell) {
	// TODO check null cell
	return 0;
}

bool map_lineOfSight(const Cell* cell1, const Cell* cell2) {
	// TODO check null cell
	return Simulator::fight->map->line_of_sight_ignored(cell1, cell2, vector<const Cell*>{});
}

ls::LSArray<ls::LSValue*>* map_getPath(const Cell* cell1, const Cell* cell2) {

	if (cell1 == nullptr or cell2 == nullptr) {
		return new ls::LSArray<ls::LSValue*>();
	}
	vector<const Cell*> path = Simulator::fight->map->get_path(cell1, vector<const Cell*>{cell2}, vector<const Cell*>{});

	auto result = new ls::LSArray<ls::LSValue*>();
	result->reserve(path.size());
	for (const Cell* cell : path) {
		result->push_back((ls::LSValue*) cell);
	}
	return result;
}

int map_getPathLength(const Cell* cell1, const Cell* cell2) {
	// TODO check null cell
	return Simulator::fight->map->get_path(cell1, vector<const Cell*>{cell2}, vector<const Cell*>{}).size();
}

int map_getType() {
	return Simulator::fight->map->type;
}

ls::LSArray<ls::LSValue*>* map_getObstacles() {
	return new ls::LSArray<ls::LSValue*>();
}

int map_getDistance(const Cell* cell1, const Cell* cell2) {
	return cell1->distance(cell2);
}

double map_getStraightDistance(const Cell* cell1, const Cell* cell2) {
	return cell1->straightDistance(cell2);
}

/*
 * LS v1 support functions (deprecated in v2)
 */

/*
 * Returns -1 for invalid cells, the distance otherwise, so always an int
 */
int map__getCellDistance(const ls::LSValue* cell1, const ls::LSValue* cell2) {

	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return -1;
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return -1;
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return -1;

	return Simulator::fight->map->getCellDistance(c1, c2);
}

/*
 * Null if the cell is not found, its ID otherwise
 */
ls::LSValue* map__getCellFromXY(const ls::LSValue* x, const ls::LSValue* y) {

	const ls::LSNumber* xn = dynamic_cast<const ls::LSNumber*>(x);
	if (xn == nullptr) return ls::LSNull::get();

	const ls::LSNumber* yn = dynamic_cast<const ls::LSNumber*>(y);
	if (yn == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(Simulator::fight->map->getCell(xn->value, yn->value)->id);
}

/*
 * Returns -1 for invalid cells, the distance otherwise, so always an float
 */
double map__getDistance(const ls::LSValue* cell1, const ls::LSValue* cell2) {

	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return -1;
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return -1;
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return -1;

	return Simulator::fight->map->getDistance(c1, c2);
}

/*
 * Always an int
 */
int map__getMapType() {
	// TODO
	return 0;
}

/*
 * Array of cells ID, int array
 */
ls::LSArray<int>* map__getObstacles() {
	// TODO
	ls::LSArray<int>* obstacles = new ls::LSArray<int>();
	return obstacles;
}

/*
 * Null for invalid arguments or no path, an int array otherwise
 */
ls::LSValue* map__getPath(const ls::LSValue* cell1, const ls::LSValue* cell2) {
	return map__getPathIgnored(cell1, cell2, ls::LSNull::get());
}

ls::LSValue* map__getPathIgnored(const ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored) {

	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return ls::LSNull::get();
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return ls::LSNull::get();
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return ls::LSNull::get();

	// Empty array if it's the same cells
	if (c1 == c2) {
		return new ls::LSArray<int>();
	}

	vector<const Cell*> ignored_cells;

	// If ignored is a number, it's an entity ID
	if (const ls::LSNumber* ignored_int = dynamic_cast<const ls::LSNumber*>(ignored)) {

		Entity* entity = Simulator::fight->getEntity(ignored_int->value);
		if (entity != nullptr and entity->cell != nullptr) {
			ignored_cells.push_back(entity->cell);
		}
	}
	// If ignored is an array, it's a array of cells ID, we add the valid cells and the entity cell
	else if (const ls::LSArray<ls::LSValue*>* ignored_array = dynamic_cast<const ls::LSArray<ls::LSValue*>*>(ignored)) {

		for (auto v : *ignored_array) {
			if (const ls::LSNumber* vn = dynamic_cast<const ls::LSNumber*>(v)) {
				const Cell* c = Simulator::fight->map->int_to_cell(vn->value);
				if (c != nullptr) {
					ignored_cells.push_back(c);
				}
			}
		}
	}

	// TODO should be Null if there is no path
	vector<const Cell*> path = Simulator::fight->map->get_path_between(c1, c2, ignored_cells);
	ls::LSArray<int>* path_int = new ls::LSArray<int>();
	for (auto c : path) {
		path_int->push_clone(c->id);
	}
	return path_int;
}

/*
 * Null for invalid arguments or no path, an int otherwise
 */
ls::LSValue* map__getPathLength(const ls::LSValue* cell1, const ls::LSValue* cell2) {
	return map__getPathLengthIgnored(cell1, cell2, ls::LSNull::get());
}

ls::LSValue* map__getPathLengthIgnored(const ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored) {

	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return ls::LSNull::get();
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return ls::LSNull::get();
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return ls::LSNull::get();

	// 0 if it's the same cells
	if (c1 == c2) {
		return 0;
	}

	vector<const Cell*> ignored_cells;

	// If ignored is an array, it's a array of cells ID, we add the valid cells and the entity cell
	if (const ls::LSArray<ls::LSValue*>* ignored_array = dynamic_cast<const ls::LSArray<ls::LSValue*>*>(ignored)) {

		for (auto v : *ignored_array) {
			if (const ls::LSNumber* vn = dynamic_cast<const ls::LSNumber*>(v)) {
				const Cell* c = Simulator::fight->map->int_to_cell(vn->value);
				if (c != nullptr) {
					ignored_cells.push_back(c);
				}
			}
		}
	}

	vector<const Cell*> path = Simulator::fight->map->get_path_between(c1, c2, ignored_cells);
	// TODO should be Null if there is no path
	return ls::LSNumber::get(path.size());
}

/*
 * This function always returns a boolean
 */
bool map__isOnSameLine(const ls::LSValue* cell1, const ls::LSValue* cell2) {

	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return false;
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return false;
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return false;

	return c1->isOnSameLine(c2);
}

/*
 * Null for invalid parameters, a boolean otherwise
 */
ls::LSValue* map__lineOfSight(const ls::LSValue* cell1, const ls::LSValue* cell2) {
	return map__lineOfSightIgnored(cell1, cell2, ls::LSNull::get());
}

ls::LSValue* map__lineOfSightIgnored(const ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored) {

	// If one of the cells is invalid, return NULL
	const ls::LSNumber* n1 = dynamic_cast<const ls::LSNumber*>(cell1);
	if (n1 == nullptr) return ls::LSNull::get();
	const Cell* c1 = Simulator::fight->map->int_to_cell(n1->value);

	const ls::LSNumber* n2 = dynamic_cast<const ls::LSNumber*>(cell2);
	if (n2 == nullptr) return ls::LSNull::get();
	const Cell* c2 = Simulator::fight->map->int_to_cell(n2->value);

	if (c1 == nullptr or c2 == nullptr) return ls::LSNull::get();

	vector<const Cell*> ignored_cells;

	// If ignored is a number, it's an entity ID
	if (const ls::LSNumber* ignored_int = dynamic_cast<const ls::LSNumber*>(ignored)) {

		Entity* entity = Simulator::fight->getEntity(ignored_int->value);
		if (entity != nullptr and entity->cell != nullptr) {
			ignored_cells.push_back(entity->cell);
		}
	}
	// If ignored is an array, it's a array of cells ID, we add the valid cells and the entity cell
	else if (const ls::LSArray<ls::LSValue*>* ignored_array = dynamic_cast<const ls::LSArray<ls::LSValue*>*>(ignored)) {

		for (auto v : *ignored_array) {
			if (const ls::LSNumber* vn = dynamic_cast<const ls::LSNumber*>(v)) {
				const Cell* c = Simulator::fight->map->int_to_cell(vn->value);
				if (c != nullptr) {
					ignored_cells.push_back(c);
				}
			}
		}
		if (Simulator::entity->cell != nullptr) {
			ignored_cells.push_back(Simulator::entity->cell);
		}
	}
	// If ignored is neither an array nor a number, we add the entity cell
	else {
		if (Simulator::entity->cell != nullptr) {
			ignored_cells.push_back(Simulator::entity->cell);
		}
	}

	// Return a boolean
	return ls::LSBoolean::get(Simulator::fight->map->line_of_sight_ignored(c1, c2, ignored_cells));
}
