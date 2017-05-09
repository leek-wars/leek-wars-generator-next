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
int entity__getLeek(void*);
int entity__getAbsoluteShield(void*);
ls::LSValue* entity__getAbsoluteShieldEntity(void*, const ls::LSValue* entity);
int entity__getAgility(void*);
ls::LSValue* entity__getAgilityEntity(void*, const ls::LSValue* entity);
int entity__getFrequency(void*);
ls::LSValue* entity__getFrequencyEntity(void*, const ls::LSValue* entity);
int entity__getCores(void*);
ls::LSValue* entity__getCoresEntity(void*, const ls::LSValue*);
int entity__getDamageReturn(void*);
ls::LSValue* entity__getDamageReturnEntity(void*, const ls::LSValue* entity);
int entity__getMagic(void*);
ls::LSValue* entity__getMagicEntity(void*, const ls::LSValue* entity);
int entity__getRelativeShield(void*);
ls::LSValue* entity__getRelativeShieldEntity(void*, const ls::LSValue* entity);
int entity__getResistance(void*);
ls::LSValue* entity__getResistanceEntity(void*, const ls::LSValue* entity);
int entity__getScience(void*);
ls::LSValue* entity__getScienceEntity(void*, const ls::LSValue* entity);
int entity__getStrength(void*);
ls::LSValue* entity__getStrengthEntity(void*, const ls::LSValue* entity);
int entity__getTotalLife(void*);
ls::LSValue* entity__getTotalLifeEntity(void*, const ls::LSValue* entity);
int entity__getTotalMP(void*);
ls::LSValue* entity__getTotalMPEntity(void*, const ls::LSValue* entity);
int entity__getTotalTP(void*);
ls::LSValue* entity__getTotalTPEntity(void*, const ls::LSValue* entity);
int entity__getWisdom(void*);
ls::LSValue* entity__getWisdomEntity(void*, const ls::LSValue* entity);
int entity__getLife(void*);
ls::LSValue* entity__getLifeEntity(void*, const ls::LSValue* entity);
int entity__getTP(void*);
ls::LSValue* entity__getTPEntity(void*, const ls::LSValue* entity);
int entity__getMP(void*);
ls::LSValue* entity__getMPEntity(void*, const ls::LSValue* entity);
int entity__getBirthTurn(void*);
ls::LSValue* entity__getBirthTurnEntity(void*, const ls::LSValue* entity);
int entity__getCell(void*);
ls::LSValue* entity__getCellEntity(void*, const ls::LSValue* entity);
ls::LSArray<int>* entity__getChips(void*);
ls::LSValue* entity__getChipsEntity(void*, const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__getEffects(void*);
ls::LSValue* entity__getEffectsEntity(void*, const ls::LSValue* entity);
int entity__getEntityTurnOrder(void*);
ls::LSValue* entity__getEntityTurnOrderEntity(void*, const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__getLaunchedEffects(void*);
ls::LSValue* entity__getLaunchedEffectsEntity(void*, const ls::LSValue* entity);
int entity__getLeekID(void*);
ls::LSValue* entity__getLeekIDEntity(void*, const ls::LSValue* entity);
int entity__getLevel(void*);
ls::LSValue* entity__getLevelEntity(void*, const ls::LSValue* entity);
ls::LSString* entity__getName(void*);
ls::LSValue* entity__getNameEntity(void*, const ls::LSValue* entity);
int entity__getNearestEnemy(void*);
ls::LSValue* entity__getSummoner(void*);
ls::LSValue* entity__getSummonerEntity(void*, const ls::LSValue* entity);
ls::LSValue* entity__getTeamID(void*);
ls::LSValue* entity__getTeamIDEntity(void*, const ls::LSValue* entity);
ls::LSValue* entity__getTeamName(void*);
ls::LSValue* entity__getTeamNameEntity(void*, const ls::LSValue* entity);
ls::LSValue* entity__getType(void*);
ls::LSValue* entity__getTypeEntity(void*, const ls::LSValue* entity);
ls::LSValue* entity__getWeapon(void*);
ls::LSValue* entity__getWeaponEntity(void*, const ls::LSValue* entity);
ls::LSArray<int>* entity__getWeapons(void*);
ls::LSValue* entity__getWeaponsEntity(void*, const ls::LSValue* entity);
ls::LSValue* entity__getCooldown(void*, const ls::LSValue* chip);
ls::LSValue* entity__getCooldownEntity(void*, const ls::LSValue* chip, const ls::LSValue* entity);

bool entity__isAlive(void*, const ls::LSValue* entity);
bool entity__isAlly(void*, const ls::LSValue* entity);
bool entity__isDead(void*, const ls::LSValue* entity);
bool entity__isEnemy(void*, const ls::LSValue* entity);
bool entity__isSummon(void*);
bool entity__isSummonEntity(void*, const ls::LSValue* entity);
ls::LSArray<ls::LSValue*>* entity__listen(void*);
int entity__moveToward(void*, const ls::LSValue* entity);
bool entity__say(void*, const ls::LSValue* message);
bool entity__setWeapon(void*, const ls::LSNumber* weapon);
int entity__useWeapon(void*, ls::LSValue* target);

#endif
