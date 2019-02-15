#ifndef FIELD_MODULE_HPP
#define FIELD_MODULE_HPP

#include <leekscript.h>
#include "CellModule.hpp"
class Color;

class FieldModule : public ls::Module {
public:
	FieldModule();
	virtual ~FieldModule();
};

const Cell* map_cell(const int x, const int y);
const Cell* map_cell1(const int id);
int map_getCellContent(const Cell* cell);
bool map_lineOfSight(const Cell* cell1, const Cell* cell2);
ls::LSArray<ls::LSValue*>* map_getPath(Cell* cell1, const Cell* cell2);
int map_getPathLength(Cell* cell1, const Cell* cell2);
int map_getType();
ls::LSArray<ls::LSValue*>* map_getObstacles();
ls::LSArray<ls::LSValue*>* map_getCells();
int map_getDistance(const Cell* cell1, const Cell* cell2);
double map_getStraightDistance(const Cell* cell1, const Cell* cell2);
bool map_mark(const Cell* cell, const Color* color, int duration);
bool map_mark_array(const ls::LSArray<ls::LSValue*> cells, const Color* color, int duration);

// V1
int map__getCellDistance(const ls::LSValue* cell1, const ls::LSValue* cell2);
ls::LSValue* map__getCellFromXY(const ls::LSValue* x, const ls::LSValue* y);
double map__getDistance(const ls::LSValue* cell1, const ls::LSValue* cell2);
int map__getMapType();
ls::LSArray<int>* map__getObstacles();
ls::LSValue* map__getPath(ls::LSValue* cell1, const ls::LSValue* cell2);
ls::LSValue* map__getPathIgnored(ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored);
ls::LSValue* map__getPathLength(ls::LSValue* cell1, const ls::LSValue* cell2);
ls::LSValue* map__getPathLengthIgnored(ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored);
bool map__isOnSameLine(const ls::LSValue* cell1, const ls::LSValue* cell2);
ls::LSValue* map__lineOfSight(const ls::LSValue* cell1, const ls::LSValue* cell2);
ls::LSValue* map__lineOfSightIgnored(const ls::LSValue* cell1, const ls::LSValue* cell2, const ls::LSValue* ignored);

#endif
