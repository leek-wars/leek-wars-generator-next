/*
 * Statistics.cpp
 *
 *  Created on: May 19, 2016
 *      Author: pierre
 */

#include "Statistics.hpp"

#include "../entity/Entity.hpp"

Statistics::Statistics() {
	// TODO Auto-generated constructor stub

}

Statistics::~Statistics() {
	// TODO Auto-generated destructor stub
}

void Statistics::add_damage(Entity* attacker, int damage, Entity* target) {

	damages.insert({attacker->id, damage});
}
