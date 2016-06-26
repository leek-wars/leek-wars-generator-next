#ifndef ENTITY_TEAM_HPP_
#define ENTITY_TEAM_HPP_

#include <vector>
#include "Entity.hpp"

class Team {

	std::map<int, int> cooldowns;

public:

	std::vector<Entity*> entities;

	Team();
	virtual ~Team();

	void add_entity(Entity* entity);

	void addCooldown(Chip* chip, int cooldown);

	bool hasCooldown(int chipID);

	int getCooldown(int chipID);

	void applyCoolDown();
};

#endif
