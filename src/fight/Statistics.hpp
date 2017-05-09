#ifndef SRC_FIGHT_STATISTICS_HPP_
#define SRC_FIGHT_STATISTICS_HPP_

#include <map>

class Entity;

class Statistics {
public:

	std::map<int, int> damages;
	std::map<int, int> heals;

	Statistics();
	virtual ~Statistics();

	void add_damage(Entity* attacker, int damage, Entity* target);
};

#endif
