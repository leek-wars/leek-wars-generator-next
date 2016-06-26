#ifndef ENTITY_LEEK_HPP_
#define ENTITY_LEEK_HPP_

#include <string>
#include "Entity.hpp"
#include "../ai/AI.hpp"

class Leek : public Entity {
public:

	Leek(Fight* fight, std::string name, int level, AI* ai);
	virtual ~Leek();

};

#endif
