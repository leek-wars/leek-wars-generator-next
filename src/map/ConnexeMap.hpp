#ifndef MAP_CONNEXEMAP_HPP_
#define MAP_CONNEXEMAP_HPP_

#include "Map.hpp"

class ConnexeMap {
public:
	Map* map;
	int** cells;

	ConnexeMap(Map* map);
	virtual ~ConnexeMap();

	int getComponent(Cell* c);
	int getComponent(int x, int y);
};

#endif
