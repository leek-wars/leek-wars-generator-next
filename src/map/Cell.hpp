#ifndef MAP_CELL_HPP_
#define MAP_CELL_HPP_

#include <ostream>
#include <leekscript.h>
class Entity;
class Map;

class Cell : public ls::LSObject {

public:

	int id;
	int x, y;

	Map* map;
	Entity* entity;

	bool walkable;
	int obstacle;
	int obstacle_size;

	bool north = true;
	bool west = true;
	bool east = true;
	bool south = true;

	Cell* parent = nullptr;
	unsigned short cost = std::numeric_limits<unsigned short>::max();
	float weight = std::numeric_limits<float>::max();
	bool visited;
	bool closed;

	Cell(Map* map, int id);
	virtual ~Cell();

	void setObstacle(int id, int size);

	void setEntity(Entity* entity);

	bool available() const;

	bool available(Cell* cell);

	int distance(const Cell* cell2) const;
	double straightDistance(const Cell* cell2) const;

	bool isEmpty() const;
	bool isObstacle() const;
	bool isWalkable() const;
	bool hasEntity() const;
	int getContent() const;
	bool isAligned(const Cell*) const;
	Entity* getEntity() const;
	int getX() const;
	int getY() const;

	virtual ls::LSValue* getClass() const override;
	virtual std::ostream& print(std::ostream& os) const override;
	virtual std::ostream& dump(std::ostream& os, int level) const override;

	friend std::ostream& operator << (std::ostream& os, const Cell* cell);
};

#endif
