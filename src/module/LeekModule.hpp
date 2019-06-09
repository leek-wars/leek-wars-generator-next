#ifndef CLASS_LEEKMODULE_HPP_
#define CLASS_LEEKMODULE_HPP_

#include <leekscript.h>
class Leek;
#include "EntityModule.hpp"

class LeekType : public EntityType {
public:
	const std::string getName() const { return "Leek"; };
};

class LeekModule : public ls::Module {
public:
	LeekModule(ls::VM* vm);
	virtual ~LeekModule();

	static const ls::LSClass* leek_clazz;
	static const std::shared_ptr<LeekType> raw_type;
	static const ls::Type* type;
};

int leek_getFarmerID(Leek* leek);
const ls::LSString* leek_getFarmerName(Leek* leek);

/*
 * V1
 */
int leek__getAIID();
ls::LSValue* leek__getAIIDEntity(const ls::LSValue* entity);
ls::LSString* leek__getAIName();
ls::LSValue* leek__getAINameEntity(const ls::LSValue* entity);
int leek__getFarmerID();
ls::LSValue* leek__getFarmerIDEntity(const ls::LSValue* entity);
ls::LSString* leek__getFarmerName();
ls::LSValue* leek__getFarmerNameEntity(const ls::LSValue* entity);

#endif
