/*
 * Item.hpp
 *
 *  Created on: 15 avr. 2016
 *      Author: pierre
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <leekscript/src/leekscript.h>

#include "../effect/Attack.hpp"

class Item : public ls::LSObject {
public:

	int id;
	std::string name;
	int cost;
	Attack attack;

	Item(int id, std::string& name, int cost, Attack& attack);
	virtual ~Item();
};

#endif
