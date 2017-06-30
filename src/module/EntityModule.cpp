#include "EntityModule.hpp"

#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../fight/Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* EntityModule::entity_clazz;
const EntityType* const EntityModule::type = new EntityType();
const ls::Type EntityModule::type_ptr(EntityModule::type, ls::Nature::POINTER, true);

EntityModule::EntityModule() : Module("Entity") {

	EntityModule::entity_clazz = this->clazz;

	field("name", ls::Type::STRING);
	field("cell", CellModule::type);
	field("level", ls::Type::INTEGER);
	field("talent", ls::Type::INTEGER);

	field("life", ls::Type::INTEGER);
	field("strength", ls::Type::INTEGER);
	field("agility", ls::Type::INTEGER);
	field("science", ls::Type::INTEGER);
	field("resistance", ls::Type::INTEGER);
	field("magic", ls::Type::INTEGER);
	field("frequency", ls::Type::INTEGER);
	field("tp", ls::Type::INTEGER);
	field("mp", ls::Type::INTEGER);
	field("relativeShield", ls::Type::INTEGER);
	field("absoluteShield", ls::Type::INTEGER);
	field("totalTP", ls::Type::INTEGER);
	field("totalMP", ls::Type::INTEGER);
	field("damageReturn", ls::Type::INTEGER);

	method("getLife", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getLife, ls::Method::NATIVE);
	method("getTotalLife", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTotalLife, ls::Method::NATIVE);
	method("getStrength", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getStrength, ls::Method::NATIVE);
	method("getAgility", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getAgility, ls::Method::NATIVE);
	method("getScience", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getScience, ls::Method::NATIVE);
	method("getMagic", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getMagic, ls::Method::NATIVE);
	method("getWisdom", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getWisdom, ls::Method::NATIVE);
	method("getFrequency", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getFrequency, ls::Method::NATIVE);
	method("getResistance", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getResistance, ls::Method::NATIVE);
	method("getTP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTP, ls::Method::NATIVE);
	method("getMP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getMP, ls::Method::NATIVE);
	method("getRelativeShield", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getRelativeShield, ls::Method::NATIVE);
	method("getAbsoluteShield", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getAbsoluteShield, ls::Method::NATIVE);
	method("getTotalTP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTotalTP, ls::Method::NATIVE);
	method("getTotalMP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTotalMP, ls::Method::NATIVE);
	method("getDamageReturn", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getDamageReturn, ls::Method::NATIVE);
	method("getCell", EntityModule::type_ptr, CellModule::type, {}, (void*) &Entity::getCell, ls::Method::NATIVE);
	method("getClosestEnemy", EntityModule::type_ptr, EntityModule::type_ptr, {}, (void*) &entity_getClosestEnemy, ls::Method::NATIVE);
	method("getWeapons", EntityModule::type_ptr, WeaponModule::array_type, {}, (void*) &Entity::getWeapons, ls::Method::NATIVE);
	method("getWeapon", EntityModule::type_ptr, WeaponModule::type, {}, (void*) &Entity::getWeapon, ls::Method::NATIVE);
	method("getLevel", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getLevel, ls::Method::NATIVE);
	method("setWeapon", {
		{EntityModule::type_ptr, ls::Type::NULLL, {WeaponModule::type}, (void*) &entity_setWeapon, ls::Method::NATIVE},
		{EntityModule::type_ptr, ls::Type::NULLL, {ls::Type::INTEGER}, (void*) &Entity::setWeaponInteger, ls::Method::NATIVE}
	});
	method("useChip", EntityModule::type_ptr, ls::Type::INTEGER, {ChipModule::type, EntityModule::type_ptr}, (void*) &Entity::useChip, ls::Method::NATIVE);
	method("useWeapon", EntityModule::type_ptr, ls::Type::INTEGER, {EntityModule::type_ptr}, (void*) &Entity::useWeapon, ls::Method::NATIVE);
	method("getChips", EntityModule::type_ptr, ChipModule::array_type, {}, (void*) &Entity::getChips, ls::Method::NATIVE);
	method("say", EntityModule::type_ptr, ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &Entity::say, ls::Method::NATIVE);
	method("moveToward", EntityModule::type_ptr, ls::Type::INTEGER, {EntityModule::type_ptr, ls::Type::INTEGER}, (void*) &Entity::moveToward, ls::Method::NATIVE);
	method("isAlive", EntityModule::type_ptr, ls::Type::BOOLEAN, {}, (void*) &Entity::isAlive, ls::Method::NATIVE);
	method("isDead", EntityModule::type_ptr, ls::Type::BOOLEAN, {}, (void*) &Entity::isDead, ls::Method::NATIVE);
	method("isAlly", EntityModule::type_ptr, ls::Type::BOOLEAN, {}, (void*) &Entity::isAlly, ls::Method::NATIVE);
	method("isEnemy", EntityModule::type_ptr, ls::Type::BOOLEAN, {}, (void*) &Entity::isEnemy, ls::Method::NATIVE);
	method("isSummon", EntityModule::type_ptr, ls::Type::BOOLEAN, {}, (void*) &Entity::isSummon, ls::Method::NATIVE);
	method("getName", EntityModule::type_ptr, ls::Type::STRING, {}, (void*) &Entity::getName, ls::Method::NATIVE);

	/*
	 * V1 functions
	 */
	static_method("_getLeek", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLeek, ls::Method::NATIVE);

	static_method("_getAbsoluteShield", {
		{ls::Type::POINTER, {}, (void*) &entity__getAbsoluteShield, ls::Method::NATIVE},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getAbsoluteShieldEntity, ls::Method::NATIVE}
	});
	static_method("_getAgility", {
		{ls::Type::POINTER, {}, (void*) &entity__getAgility, ls::Method::NATIVE},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getAgilityEntity, ls::Method::NATIVE}
	});
	static_method("_getBirthTurn", {
		{ls::Type::INTEGER, {}, (void*) &entity__getBirthTurn},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getBirthTurnEntity}
	});
	static_method("_getCell", {
		{ls::Type::INTEGER, {}, (void*) &entity__getCell},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCellEntity}
	});
	static_method("_getChips", {
		{ls::Type::INT_ARRAY, {}, (void*) &entity__getChips},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getChipsEntity},
	});
	static_method("_getCores", {
		{ls::Type::INTEGER, {}, (void*) &entity__getCores},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCoresEntity},
	});
	static_method("_getDamageReturn", {
		{ls::Type::INTEGER, {}, (void*) &entity__getDamageReturn},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getDamageReturnEntity}
	});
	static_method("_getEffects", {
		{ls::Type::PTR_ARRAY, {}, (void*) &entity__getEffects},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getEffectsEntity}
	});
	static_method("_getEntityTurnOrder", {
		{ls::Type::INTEGER, {}, (void*) &entity__getEntityTurnOrder},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getEntityTurnOrderEntity}
	});
	static_method("_getFrequency", {
		{ls::Type::INTEGER, {}, (void*) &entity__getFrequency},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getFrequencyEntity}
	});
	static_method("_getLaunchedEffects", {
		{ls::Type::PTR_ARRAY, {}, (void*) &entity__getLaunchedEffects},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLaunchedEffectsEntity}
	});
	static_method("_getLeekID", {
		{ls::Type::INTEGER, {}, (void*) &entity__getLeekID},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLeekIDEntity}
	});
	static_method("_getLevel", {
		{ls::Type::INTEGER, {}, (void*) &entity__getLevel},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLevelEntity}
	});
	static_method("_getLife", {
		{ls::Type::INTEGER, {}, (void*) &entity__getLife},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLifeEntity}
	});
	static_method("_getMagic", {
		{ls::Type::INTEGER, {}, (void*) &entity__getMagic},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getMagicEntity}
	});
	static_method("_getMP", {
		{ls::Type::INTEGER, {}, (void*) &entity__getMP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getMPEntity}
	});
	static_method("_getName", {
		{ls::Type::STRING, {}, (void*) &entity__getName},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getNameEntity}
	});
	static_method("_getNearestEnemy", {
		{ls::Type::INTEGER, {}, (void*) &entity__getNearestEnemy}
	});
	static_method("_getRelativeShield", {
		{ls::Type::INTEGER, {}, (void*) &entity__getRelativeShield},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getRelativeShieldEntity}
	});
	static_method("_getResistance", {
		{ls::Type::INTEGER, {}, (void*) &entity__getResistance},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getResistanceEntity}
	});
	static_method("_getScience", {
		{ls::Type::INTEGER, {}, (void*) &entity__getScience},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getScienceEntity}
	});
	static_method("_getStrength", {
		{ls::Type::INTEGER, {}, (void*) &entity__getStrength},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getStrengthEntity}
	});
	static_method("_getSummoner", {
		{ls::Type::INTEGER, {}, (void*) &entity__getSummoner},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getSummonerEntity}
	});
	static_method("_getTeamID", {
		{ls::Type::INTEGER, {}, (void*) &entity__getTeamID},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTeamIDEntity}
	});
	static_method("_getTeamName", {
		{ls::Type::STRING, {}, (void*) &entity__getTeamName},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTeamNameEntity}
	});
	static_method("_getTotalLife", {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalLife},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalLifeEntity}
	});
	static_method("_getTotalMP", {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalMP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalMPEntity}
	});
	static_method("_getTotalTP", {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalTP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalTPEntity}
	});
	static_method("_getTP", {
		{ls::Type::INTEGER, {}, (void*) &entity__getTP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTPEntity}
	});
	static_method("_getType", {
		{ls::Type::INTEGER, {}, (void*) &entity__getType},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTypeEntity}
	});
	static_method("_getWeapon", {
		{ls::Type::POINTER, {}, (void*) &entity__getWeapon},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWeaponEntity}
	});
	static_method("_getWeapons", {
		{ls::Type::INT_ARRAY, {}, (void*) &entity__getWeapons},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWeaponsEntity}
	});
	static_method("_getWisdom", {
		{ls::Type::INTEGER, {}, (void*) &entity__getWisdom},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWisdomEntity}
	});
	static_method("_isAlive", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isAlive);
	static_method("_isAlly", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isAlly);
	static_method("_isDead", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isDead);
	static_method("_isEnemy", ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isEnemy);
	static_method("_isSummon", {
		{ls::Type::BOOLEAN, {}, (void*) &entity__isSummon},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__isSummonEntity},
	});

	static_method("_getCooldown", {
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCooldown},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &entity__getCooldownEntity},
	});

	static_method("_listen", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__listen);
	static_method("_moveToward", ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &entity__moveToward);
	static_method("_say", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__say);
	static_method("_setWeapon", ls::Type::BOOLEAN, {ls::Type::NUMBER}, (void*) &entity__setWeapon);
	static_method("_useWeapon", ls::Type::INTEGER, {ls::Type::NUMBER}, (void*) &entity__useWeapon);
}

EntityModule::~EntityModule() {}

const Entity* entity_getClosestEnemy(Entity* entity) {
	return Simulator::fight->teams[(entity->team + 1) % 2]->entities[0];
}

const Weapon* entity_getWeapon(Entity* entity) {
	return (Weapon*) entity->getWeapon();
}

const ls::LSArray<Weapon*>* entity_getWeapons(Entity* entity) {
	return (const ls::LSArray<Weapon*>*) entity->getField("weapons");
}

const ls::LSNull* entity_setWeapon(Entity* entity, const Weapon* weapon) {
	entity->setWeapon(weapon);
	return (ls::LSNull*) ls::LSNull::get();
}

/*
 * LS v1 support functions (deprecated in v2)
 */

/*
 * Internal function to get a entity from the function argument
 * Null -> my entity
 * Number -> an entity id, try to get it
 */
inline Entity* entity__getEntity(const ls::LSValue* entity) {
	if (dynamic_cast<const ls::LSNull*>(entity)) {
		return Simulator::entity;
	}
	if (const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(entity)) {
		return Simulator::fight->getEntity(n->value);
	}
	return nullptr;
}

/*
 * Internal function to get an entity characteristic
 */
inline ls::LSValue* entity__getCharacteristic(const ls::LSValue* entity, Characteristic charac) {

	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(e->getCharacteristic(charac));
}

/*
 * Characteristics methods, all the same
 * Null if invalid entity, int otherwise
 */
int entity__getAbsoluteShield(void*) {
	return Simulator::entity->getAbsoluteShield();
}
ls::LSValue* entity__getAbsoluteShieldEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::ABSOLUTE_SHIELD);
}
int entity__getAgility(void*) {
	return Simulator::entity->getAgility();
}
ls::LSValue* entity__getAgilityEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::AGILITY);
}
int entity__getFrequency(void*) {
	return Simulator::entity->getFrequency();
}
ls::LSValue* entity__getFrequencyEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::FREQUENCY);
}
int entity__getCores(void*) {
	return 0; // was already deprecated in v1
}
ls::LSValue* entity__getCoresEntity(void*, const ls::LSValue*) {
	return ls::LSNumber::get(0); // was already deprecated in v1
}
int entity__getDamageReturn(void*) {
	return Simulator::entity->getDamageReturn();
}
ls::LSValue* entity__getDamageReturnEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::DAMAGE_RETURN);
}
int entity__getMagic(void*) {
	return Simulator::entity->getMagic();
}
ls::LSValue* entity__getMagicEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MAGIC);
}
int entity__getRelativeShield(void*) {
	return Simulator::entity->getRelativeShield();
}
ls::LSValue* entity__getRelativeShieldEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RELATIVE_SHIELD);
}
int entity__getResistance(void*) {
	return Simulator::entity->getResistance();
}
ls::LSValue* entity__getResistanceEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RESISTANCE);
}
int entity__getScience(void*) {
	return Simulator::entity->getScience();
}
ls::LSValue* entity__getScienceEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::SCIENCE);
}
int entity__getStrength(void*) {
	return Simulator::entity->getStrength();
}
ls::LSValue* entity__getStrengthEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::STRENGTH);
}
int entity__getTotalLife(void*) {
	return Simulator::entity->getTotalLife();
}
ls::LSValue* entity__getTotalLifeEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::LIFE);
}
int entity__getTotalMP(void*) {
	return Simulator::entity->getTotalMP();
}
ls::LSValue* entity__getTotalMPEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MP);
}
int entity__getTotalTP(void*) {
	return Simulator::entity->getTotalTP();
}
ls::LSValue* entity__getTotalTPEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::TP);
}
int entity__getWisdom(void*) {
	return Simulator::entity->getWisdom();
}
ls::LSValue* entity__getWisdomEntity(void*, const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::WISDOM);
}

int entity__getLife(void*) {
	return Simulator::entity->getLife();
}
ls::LSValue* entity__getLifeEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->life);
}

int entity__getTP(void*) {
	return Simulator::entity->getTP();
}
ls::LSValue* entity__getTPEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getTP());
}

int entity__getMP(void*) {
	return Simulator::entity->getMP();
}
ls::LSValue* entity__getMPEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getMP());
}

int entity__getBirthTurn(void*) {
	return 0;
}
ls::LSValue* entity__getBirthTurnEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(0);
}

int entity__getCell(void*) {
	return Simulator::entity->cell->id;
}
ls::LSValue* entity__getCellEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->cell->id);
}

ls::LSArray<int>* entity__getChips(void*) {
	// TODO Int array
//	return Simulator::entity->chips.clone();
}
ls::LSValue* entity__getChipsEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->chips.clone();
}

ls::LSArray<ls::LSValue*>* entity__getEffects(void*) {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getEffectsEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getEntityTurnOrder(void*) {
	// TODO
}
ls::LSValue* entity__getEntityTurnOrderEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSArray<ls::LSValue*>* entity__getLaunchedEffects(void*) {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getLaunchedEffectsEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLeekID(void*) {
	return Simulator::entity->id;
}
ls::LSValue* entity__getLeekIDEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLevel(void*) {
	return Simulator::entity->level;
}
ls::LSValue* entity__getLevelEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->level);
}

ls::LSString* entity__getName(void*) {
	return new ls::LSString(Simulator::entity->name);
}
ls::LSValue* entity__getNameEntity(void*, const ls::LSValue* entity) {
	std::cout << "getName " << (void*)entity << std::endl;
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->name);
}

int entity__getNearestEnemy(void*) {
	return Simulator::entity->getClosestEnemy()->id;
}

ls::LSValue* entity__getSummoner(void*) {
	// TODO
}
ls::LSValue* entity__getSummonerEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getTeamID(void*) {
	// TODO
//	return LSNumber::get(e->team_id);
}
ls::LSValue* entity__getTeamIDEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->team_id);
}

/*
 * Null or string
 */
ls::LSValue* entity__getTeamName(void*) {
//	return new LSString(e->team_name);
}
ls::LSValue* entity__getTeamNameEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->team_name);
}

ls::LSValue* entity__getType(void*) {
	// TODO
}
ls::LSValue* entity__getTypeEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getWeapon(void*) {
	// TODO
}
ls::LSValue* entity__getWeaponEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapon->clone();
}

ls::LSArray<int>* entity__getWeapons(void*) {
	// TODO
}
ls::LSValue* entity__getWeaponsEntity(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapons.clone();
}

bool entity__isAlive(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isAlive();
}

bool entity__isDead(void*, const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isDead();
}

bool entity__isAlly(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isEnemy(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isSummon(void*) {
	// TODO
	return false;
}
bool entity__isSummonEntity(void*, const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return false;
	return false;
}

int entity__getLeek(void*) {
	return Simulator::entity->id;
}

ls::LSArray<ls::LSValue*>* entity__listen(void*) {
	// TODO
	return new ls::LSArray<ls::LSValue*>();
}

int entity__moveToward(void*, const ls::LSValue* entity) {
	auto e = entity__getEntity(entity);
	if (e == nullptr) {
		return 0;
	}
	return Simulator::entity->moveToward(e);
}

bool entity__say(void*, const ls::LSValue* message) {
	return Simulator::entity->say(message);
}

bool entity__setWeapon(void* fun, const ls::LSNumber* weapon) {
	return Simulator::entity->setWeaponInteger(weapon->value);
}

/*
 * Null or int
 */
ls::LSValue* entity__getCooldown(void*, const ls::LSValue* chip) {
	// TODO
}
ls::LSValue* entity__getCooldownEntity(void*, const ls::LSValue* chip, const ls::LSValue* entity) {
	// TODO
}

ls::LSValue* entity__resurrect(void*) {
	// TODO
}
ls::LSValue* entity__summon(void*) {
	// TODO
}
ls::LSValue* entity__useChip(void*) {
	// TODO
}
ls::LSValue* entity__useChipOnCell(void*) {
	// TODO
}

int entity__useWeapon(void*, ls::LSValue* target) {
	auto e = entity__getEntity(target);
	return Simulator::entity->useWeapon(e);
}
