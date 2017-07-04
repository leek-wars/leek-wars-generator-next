#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <vector>
#include "../../lib/json.hpp"
class Fight;
class Action;
class Entity;
class Map;

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
	void add_entity_logs(Entity* entity);

	int getNextId();

	Json json();

	void addEntity(Entity* entity, bool valid_ai);

	void addMap(Map* map);
};

#endif
