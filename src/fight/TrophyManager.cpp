#include "TrophyManager.hpp"
#include "Fight.hpp"

void TrophyManager::unlock_roxxor(Entity* entity) {
	unlock_trophy(entity, Trophy::ROXXOR);
}

void TrophyManager::unlock_trophy(Entity* entity, Trophy trophy) {
	if (trophies.find(entity->farmer) == trophies.end()) {
		trophies.insert({entity->farmer, {}});
	}
	auto& farmer_trophies = trophies.at(entity->farmer);
	if (farmer_trophies.find(trophy) == farmer_trophies.end()) {
		farmer_trophies.insert({trophy, {}});
	}
	farmer_trophies.at(trophy).push_back({trophy, fight->turn(), entity->id});
}
