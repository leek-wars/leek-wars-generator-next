#ifndef FIGHT_HPP_
#define FIGHT_HPP_

#include <leekscript/src/leekscript.h>

#include <vector>
class Entity;
class Team;
#include "Report.hpp"
#include "Order.hpp"
class Map;
class Chip;
class Cell;
#include "../action/Actions.hpp"
#include "Statistics.hpp"

class Fight {
public:

	static const int MAX_TURNS = 64;

	Map* map;
	std::vector<Team*> teams;
	std::map<int, Entity*> entities;
	int turn;
	Order order;
	Actions actions;
	Statistics statistics;
	int type;
	int context;

	Fight();
	virtual ~Fight();

	Report* start(ls::VM& vm);

	Entity* getEntity(int id);

	int moveEntity(Entity* entity, const std::vector<const Cell*> path);

	bool generateCritical(Entity* entity) const;

	bool hasCooldown(const Entity* entity, const Chip* chip) const;

	int useWeapon(Entity* launcher, Cell* target);
	int useChip(Entity* caster, Cell* cell, Chip* chip);
};

#endif
