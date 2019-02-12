#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <leekscript.h>

class Fight;
class Entity;

class Simulator {
public:
	static Fight* fight;
	static Entity* entity;

	static Entity* getEntity(const ls::LSValue* entity);
};

#endif
