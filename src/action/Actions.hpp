#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <vector>
#include "../../lib/json.hpp"
class Fight;
class Action;
class Entity;
class Map;
class Cell;

class Actions {
public:

	Fight* fight;
	std::vector<Action*> actions;
	int effect_id = 0;
	Json logs = Json::object();

	Actions(Fight* fight);
	~Actions();

	int getEffectId();

	void add(Action* action);
	void add_entity_log(Entity* entity, std::string log);
	bool add_mark(Entity* entity, std::vector<const Cell*> cells, int color, int duration);
	bool add_log(Entity* entity, Json&& log, int cost);

	int getNextId();

	Json json();

	void addMap(Map* map);
};

#endif
