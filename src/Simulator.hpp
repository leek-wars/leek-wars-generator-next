#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

class Fight;
class Entity;

class Simulator {
public:
	Simulator();
	virtual ~Simulator();

	static Fight* fight;
	static Entity* entity;
};

#endif
