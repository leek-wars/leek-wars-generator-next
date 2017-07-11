#ifndef MAP_CONNEXEMAP_HPP_
#define MAP_CONNEXEMAP_HPP_

#include "Field.hpp"

class ConnexeMap {
public:
	Field* field;
	int** cells;

	ConnexeMap(Field* field);
	virtual ~ConnexeMap();

	int getComponent(Cell* c);
	int getComponent(int x, int y);
};

#endif
