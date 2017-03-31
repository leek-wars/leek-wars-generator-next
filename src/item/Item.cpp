/*
 * Item.cpp
 *
 *  Created on: 15 avr. 2016
 *      Author: pierre
 */

#include "Item.hpp"

Item::Item(int id, std::string& name, int cost, Attack* attack)
	: id(id), name(name), cost(cost), attack(attack) {
	native = true;
	refs = 1;
}

Item::~Item() {}
