#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include "../item/Weapon.hpp"
#include "../fight/Fight.hpp"

class FightManager {
public:

	FightManager();

	ls::VM vm;
	ls::VM vm_v1;
	std::map<std::string, Weapon*> weapons;

	Report* start(Fight& fight);
};

#endif
