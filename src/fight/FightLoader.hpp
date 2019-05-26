#ifndef FIGHT_LOADER_HPP_
#define FIGHT_LOADER_HPP_

#include <string>
class FightManager;
class Fight;

class FightLoader {
public:
	static Fight* load(const FightManager& manager, std::string file, bool nocache);
};

#endif
