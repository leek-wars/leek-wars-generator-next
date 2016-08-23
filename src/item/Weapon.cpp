/*
 * Weapon.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: pierre
 */

#include "Weapon.hpp"

Weapon::Weapon(int id, std::string&& name, int cost, Attack&& attack)
	: Item(id, name, cost, attack) {

	readonly = true;
	values["name"] = new ls::LSString(name);
}

Weapon::~Weapon() {
//	cout << "~Weapon()" << endl;
}

