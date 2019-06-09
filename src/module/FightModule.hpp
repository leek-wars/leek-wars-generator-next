#ifndef CLASS_FIGHTMODULE_HPP_
#define CLASS_FIGHTMODULE_HPP_

#include <leekscript.h>
class Fight;
class Entity;

class FightClass : public ls::LSObject {};

class FightModule : public ls::Module {
public:
	FightModule(ls::VM* vm);
	virtual ~FightModule();
};

int fight_getTurn();
Entity* fight_getEntity();
int fight_getType();
int fight_getContext();

// V1
int fight__getEntity();

#endif
