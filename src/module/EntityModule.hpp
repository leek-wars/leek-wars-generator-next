#ifndef CLASS_ENTITYMODULE_HPP_
#define CLASS_ENTITYMODULE_HPP_

#include <leekscript/src/leekscript.h>

class Entity;
class Weapon;
#include "CellModule.hpp"
class Chip;
class Effect;

class EntityType : public ls::ObjectRawType {
public:
	virtual const std::string getName() const override { return "entity"; };
	virtual const std::string getClass() const override { return "Entity"; };
};

class EntityModule : public ls::Module {
public:
	EntityModule();
	virtual ~EntityModule();

	static const ls::LSClass* entity_clazz;
	static const EntityType* const type;
	static const ls::Type type_ptr;
};

const Entity* entity_getClosestEnemy(Entity* entity);
const ls::LSArray<ls::LSValue>* entity_listen(Entity* entity);
const ls::LSNull* entity_say(Entity* entity);
const ls::LSNull* entity_setWeapon(Entity* entity, const Weapon* weapon);


// V1 functions
int entity__getLeek();
int entity__getAbsoluteShield();
ls::LSValue* entity__getAbsoluteShieldEntity(const ls::LSValue* entity);
int entity__getAgility();
ls::LSValue* entity__getAgilityEntity(const ls::LSValue* entity);
int entity__getFrequency();
ls::LSValue* entity__getFrequencyEntity(const ls::LSValue* entity);
int entity__getCores();
ls::LSValue* entity__getCoresEntity(const ls::LSValue*);
int entity__getDamageReturn();
ls::LSValue* entity__getDamageReturnEntity(const ls::LSValue* entity);
int entity__getMagic();
ls::LSValue* entity__getMagicEntity(const ls::LSValue* entity);
int entity__getRelativeShield();
ls::LSValue* entity__getRelativeShieldEntity(const ls::LSValue* entity);
int entity__getResistance();
ls::LSValue* entity__getResistanceEntity(const ls::LSValue* entity);
int entity__getScience();
ls::LSValue* entity__getScienceEntity(const ls::LSValue* entity);
int entity__getStrength();
ls::LSValue* entity__getStrengthEntity(const ls::LSValue* entity);
int entity__getTotalLife();
ls::LSValue* entity__getTotalLifeEntity(const ls::LSValue* entity);
int entity__getTotalMP();
ls::LSValue* entity__getTotalMPEntity(const ls::LSValue* entity);
int entity__getTotalTP();
ls::LSValue* entity__getTotalTPEntity(const ls::LSValue* entity);
int entity__getWisdom();
ls::LSValue* entity__getWisdomEntity(const ls::LSValue* entity);
int entity__getLife();
ls::LSValue* entity__getLifeEntity(const ls::LSValue* entity);
int entity__getTP();
ls::LSValue* entity__getTPEntity(const ls::LSValue* entity);
int entity__getMP();
ls::LSValue* entity__getMPEntity(const ls::LSValue* entity);
int entity__getBirthTurn();
ls::LSValue* entity__getBirthTurnEntity(const ls::LSValue* entity);
int entity__getCell();
ls::LSValue* entity__getCellEntity(const ls::LSValue* entity);
ls::LSArray<int>* entity__getChips();
ls::LSValue* entity__getChipsEntity(const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__getEffects();
ls::LSValue* entity__getEffectsEntity(const ls::LSValue* entity);
int entity__getEntityTurnOrder();
ls::LSValue* entity__getEntityTurnOrderEntity(const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__getLaunchedEffects();
ls::LSValue* entity__getLaunchedEffectsEntity(const ls::LSValue* entity);
int entity__getLeekID();
ls::LSValue* entity__getLeekIDEntity(const ls::LSValue* entity);
int entity__getLevel();
ls::LSValue* entity__getLevelEntity(const ls::LSValue* entity);
ls::LSString* entity__getName();
ls::LSValue* entity__getNameEntity(const ls::LSValue* entity);
int entity__getNearestEnemy(void*);
ls::LSValue* entity__getSummoner();
ls::LSValue* entity__getSummonerEntity(const ls::LSValue* entity);
ls::LSValue* entity__getTeamID();
ls::LSValue* entity__getTeamIDEntity(const ls::LSValue* entity);
ls::LSValue* entity__getTeamName();
ls::LSValue* entity__getTeamNameEntity(const ls::LSValue* entity);
ls::LSValue* entity__getType();
ls::LSValue* entity__getTypeEntity(const ls::LSValue* entity);
ls::LSValue* entity__getWeapon();
ls::LSValue* entity__getWeaponEntity(const ls::LSValue* entity);
ls::LSArray<int>* entity__getWeapons();
ls::LSValue* entity__getWeaponsEntity(const ls::LSValue* entity);
ls::LSValue* entity__getCooldown(const ls::LSValue* chip);
ls::LSValue* entity__getCooldownEntity(const ls::LSValue* chip, const ls::LSValue* entity);

bool entity__isAlive(const ls::LSValue* entity);
bool entity__isAlly(const ls::LSValue* entity);
bool entity__isDead(const ls::LSValue* entity);
bool entity__isEnemy(const ls::LSValue* entity);
bool entity__isSummon();
bool entity__isSummonEntity(const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__listen();
int entity__moveToward(void*, const ls::LSValue* entity);
bool entity__say(const ls::LSValue* message);
bool entity__setWeapon(const ls::LSValue* weapon);


int entity__useWeapon(void*, ls::LSValue* target);

#endif
