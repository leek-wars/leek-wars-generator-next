#ifndef ENTITY_ENTITY_OUTPUT_HPP_
#define ENTITY_ENTITY_OUTPUT_HPP_

#include "leekscript.h"
class Entity;

class EntityOutput : public ls::OutputStream {
	Entity* entity;
	std::ostringstream oss;
public:
	EntityOutput(Entity* entity) : entity(entity) {}
	virtual std::ostream& stream() override {
		return oss;
	}
	virtual void end() override;
};

#endif