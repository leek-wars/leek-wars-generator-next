#ifndef CLASS_MAPMODULE_HPP_
#define CLASS_MAPMODULE_HPP_

#include <leekscript.h>
#include "CellModule.hpp"

class MapModule : public ls::Module {
public:
	MapModule();
	virtual ~MapModule();
};

const Cell* map_cell(const int x, const int y);
int map_getCellContent(const Cell* cell);
bool map_lineOfSight(const Cell* cell1, const Cell* cell2);
ls::LSArray<ls::LSValue*>* map_getPath(Cell* cell1, const Cell* cell2);
int map_getPathLength(Cell* cell1, const Cell* cell2);
int map_getType();
ls::LSArray<ls::LSValue*>* map_getObstacles();
int map_getDistance(const Cell* cell1, const Cell* cell2);
double map_getStraightDistance(const Cell* cell1, const Cell* cell2);

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
