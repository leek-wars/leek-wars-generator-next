#ifndef ENTITY_LEEK_HPP_
#define ENTITY_LEEK_HPP_

#include <string>
#include "Entity.hpp"
#include "../ai/AI.hpp"

class Leek : public Entity {
public:
	int skin = 1;
	int hat = 0;

	Leek(Fight* fight, std::string name, int level, AI* ai, int skin, int hat);
	virtual ~Leek();

};

#endif
