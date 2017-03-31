#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <vector>

#include "../../lib/json.hpp"

class Action;
class Entity;
class Map;

class Actions {

	std::vector<Action*> actions;
	int effect_id = 0;

public:

	~Actions();

	/*
	private final JSONArray leeks = new JSONArray();
	private final JSONObject map = new JSONObject();
	private final JSONArray team1 = new JSONArray();
	private final JSONArray team2 = new JSONArray();
	*/

	int getEffectId();

	void add(Action* action);

	int getNextId();

	Json json();

	void addEntity(Entity* entity, bool valid_ai);

	void addMap(Map* map);
};

#endif
