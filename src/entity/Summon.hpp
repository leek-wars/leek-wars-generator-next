/*
 * Summon.hpp
 *
 *  Created on: May 4, 2016
 *      Author: pierre
 */

#ifndef ENTITY_SUMMON_HPP_
#define ENTITY_SUMMON_HPP_

#include "Entity.hpp"

class Summon: public Entity {
public:
	Summon(Fight* fight, int level);
	virtual ~Summon();
};

#endif /* ENTITY_SUMMON_HPP_ */
