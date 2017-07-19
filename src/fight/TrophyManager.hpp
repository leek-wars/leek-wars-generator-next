#ifndef TROPHY_MANAGER_HPP
#define TROPHY_MANAGER_HPP

#include <map>
#include <vector>
#include "../entity/Entity.hpp"

enum class Trophy {
	ROXXOR = 75
};

struct UnlockedTrophy {
	Trophy trophy;
	int turn;
	int entity;
};

class TrophyManager {
public:
	Fight* fight;
	std::map<int, std::map<Trophy, std::vector<UnlockedTrophy>>> trophies;

	void unlock_roxxor(Entity* entity);
	void unlock_trophy(Entity* entity, Trophy trophy);
};

#endif
