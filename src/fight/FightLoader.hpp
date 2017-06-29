#ifndef FIGHT_LOADER_HPP_
#define FIGHT_LOADER_HPP_

#include <string>

class Fight;

class FightLoader {
public:
	static Fight* load(std::string file);
};

#endif
