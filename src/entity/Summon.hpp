#ifndef ENTITY_SUMMON_HPP_
#define ENTITY_SUMMON_HPP_

#include "Entity.hpp"

class Summon: public Entity {
public:
	Summon(Fight* fight, int level);
	virtual ~Summon();
};

#endif
