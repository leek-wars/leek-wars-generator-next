#include "Team.hpp"
#include "../fight/Fight.hpp"

Team::Team(int id) : id(id) {}

Team::~Team() {
	for (auto& entity : entities) {
		delete entity;
	}
}

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
			cooldowns[c.first] = c.second - 1;
		}
	}
}

bool Team::is_dead() const {
	for (auto& l : entities) {
		if (!l->isDead()) {
			return false;
		}
	}
	return true;
}

bool Team::is_alive() const {
	return !is_dead();
}
