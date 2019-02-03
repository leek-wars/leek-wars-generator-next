/*
 * Handle the computation of entities starting order
 */
#ifndef SRC_FIGHT_STARTORDER_HPP_
#define SRC_FIGHT_STARTORDER_HPP_

#include <vector>
#include "../entity/Entity.hpp"
class FightManager;

class StartOrder {

	std::vector<std::vector<Entity*>> teams;
	unsigned total_entities = 0;

public:
	StartOrder();
	virtual ~StartOrder();

	void addEntity(Entity* entity);
	std::vector<Entity*> compute(FightManager* manager);
};

#endif
