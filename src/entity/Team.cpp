/*
 * Team.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: pierre
 */

#include "Team.hpp"
#include "../fight/Fight.hpp"

Team::Team() {}

Team::~Team() {}

void Team::add_entity(Entity* entity) {
	entities.push_back(entity);
}

// Add a team cooldown (for example for summons chips)
void Team::addCooldown(Chip* chip, int cooldown) {

	cooldowns[chip->id] = cooldown == -1 ? Fight::MAX_TURNS + 2 : cooldown;
}

// Team has cooldown for this chip?
bool Team::hasCooldown(int chipID) {
	return cooldowns.find(chipID) != cooldowns.end();
}

// Get current cooldown for a chip
int Team::getCooldown(int chipID) {
	if (!hasCooldown(chipID)) {
		return 0;
	}
	return cooldowns[chipID];
}

// Decrement cooldowns
void Team::applyCoolDown() {
	for (auto c : cooldowns) {
		if (c.second <= 1) {
			cooldowns.erase(c.first);
		} else {
			cooldowns[c.first] =  c.second - 1;
		}
	}
}
