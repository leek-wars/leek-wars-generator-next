#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include "../item/Weapon.hpp"
#include "../item/Chip.hpp"
#include "../fight/Fight.hpp"
#include <functional>
#include <chrono>

class FightManager {
public:

	static FightManager* current;
	std::function<void(Report*)> callback;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

	FightManager();

	ls::VM vm;
	ls::VM vm_v1;
	std::map<std::string, Weapon*> weapons;
	std::map<std::string, Chip*> chips;
	Fight* fight;

	void start(Fight& fight, std::function<void(Report*)> callback);
	void crash();
	void end(Report* report);
};

#endif
