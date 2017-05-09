#ifndef FIGHT_ORDER_HPP_
#define FIGHT_ORDER_HPP_

#include <vector>
class Entity;
class Summon;

class Order {

public:

	std::vector<Entity*> entities;
	int position = 0;
	unsigned int turn = 1;

	Order();
	virtual ~Order();

	void addEntity(Entity* entity);
	void addSummon(Entity* owner, Summon* invoc);
	void addEntity(unsigned int index, Entity* invoc);
	void removeEntity(Entity* entity);
	Entity* current();
	int getTurn();
	int getEntityTurnOrder(Entity* e);
	bool next();
	Entity* getNextPlayer();
	Entity* getPreviousPlayer();
	int getPosition() const;
};

std::ostream& operator << (std::ostream& os, Order& order);

#endif
