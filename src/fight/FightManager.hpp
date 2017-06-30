#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include "../item/Weapon.hpp"
#include "../item/Chip.hpp"
#include "../fight/Fight.hpp"

class FightManager {
public:

	FightManager();

	ls::VM vm;
	ls::VM vm_v1;
	std::map<std::string, Weapon*> weapons;
	std::map<std::string, Chip*> chips;
	Fight* fight;

	Report* start(Fight& fight);
	Report* crash();
};

#endif
