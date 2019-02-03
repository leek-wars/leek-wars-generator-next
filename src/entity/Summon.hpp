#ifndef ENTITY_SUMMON_HPP_
#define ENTITY_SUMMON_HPP_

#include "Entity.hpp"

class Summon: public Entity {
public:
	Entity* owner;

	Summon(Fight* fight, int level);
	virtual ~Summon();

	virtual int getOwnerId() const override;
};

#endif
