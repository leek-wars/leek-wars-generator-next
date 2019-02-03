#include "Summon.hpp"

Summon::Summon(Fight* fight, int level) : Entity(fight, "Summon", level) {}

Summon::~Summon() {}

int Summon::getOwnerId() const {
	return -1;
}