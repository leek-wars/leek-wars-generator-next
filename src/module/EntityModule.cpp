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
	method("getTotalLife", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getStrength, ls::Method::NATIVE);
	method("getStrength", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getStrength, ls::Method::NATIVE);
	method("getAgility", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getAgility, ls::Method::NATIVE);
	method("getScience", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getScience, ls::Method::NATIVE);
	method("getMagic", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getMagic, ls::Method::NATIVE);
	method("getWisdom", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getWisdom, ls::Method::NATIVE);
	method("getFrequency", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getFrequency, ls::Method::NATIVE);
	method("getResistance", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getResistance, ls::Method::NATIVE);
	method("getTP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTP, ls::Method::NATIVE);
	method("getRelativeShield", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getRelativeShield, ls::Method::NATIVE);
	method("getAbsoluteShield", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getAbsoluteShield, ls::Method::NATIVE);
	method("getTotalTP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTotalTP, ls::Method::NATIVE);
	method("getTotalMP", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getTotalMP, ls::Method::NATIVE);
	method("getDamageReturn", EntityModule::type_ptr, ls::Type::INTEGER, {}, (void*) &Entity::getDamageReturn, ls::Method::NATIVE);
	method("getCell", EntityModule::type_ptr, CellModule::type, {}, (void*) &Entity::getCell, ls::Method::NATIVE);
	method("getClosestEnemy", EntityModule::type_ptr, EntityModule::type_ptr, {}, (void*) &entity_getClosestEnemy, ls::Method::NATIVE);
	method("getWeapons", EntityModule::type_ptr, WeaponModule::array_type, {}, (void*) &Entity::getWeapons, ls::Method::NATIVE);
	method("getWeapon", EntityModule::type_ptr, WeaponModule::type, {}, (void*) &Entity::getWeapon, ls::Method::NATIVE);

	method("setWeapon", {
		{EntityModule::type_ptr, ls::Type::NULLL, {WeaponModule::type}, (void*) &entity_setWeapon, ls::Method::NATIVE},
		{EntityModule::type_ptr, ls::Type::NULLL, {ls::Type::INTEGER}, (void*) &Entity::setWeaponInteger, ls::Method::NATIVE}
	});

	method("useChip", EntityModule::type_ptr, ls::Type::INTEGER, {ChipModule::type, EntityModule::type_ptr}, (void*) &Entity::useChip, ls::Method::NATIVE);

	method("useWeapon", EntityModule::type_ptr, ls::Type::INTEGER, {EntityModule::type_ptr}, (void*) &Entity::useWeapon, ls::Method::NATIVE);

	method("getChips", EntityModule::type_ptr, ChipModule::array_type, {}, (void*) &Entity::getChips, ls::Method::NATIVE);

	method("say", EntityModule::type_ptr, ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &Entity::say, ls::Method::NATIVE);

	method("moveToward", EntityModule::type_ptr, ls::Type::INTEGER, {EntityModule::type_ptr, ls::Type::INTEGER}, (void*) &Entity::moveToward, ls::Method::NATIVE);

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
	static_method("_say", ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__say);
	static_method("_setWeapon", ls::Type::BOOLEAN, {ls::Type::NUMBER}, (void*) &entity__setWeapon);
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
int entity__getAbsoluteShield() {
	return Simulator::entity->getAbsoluteShield();
}
ls::LSValue* entity__getAbsoluteShieldEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::ABSOLUTE_SHIELD);
}
int entity__getAgility() {
	return Simulator::entity->getAgility();
}
ls::LSValue* entity__getAgilityEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::AGILITY);
}
int entity__getFrequency() {
	return Simulator::entity->getFrequency();
}
ls::LSValue* entity__getFrequencyEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::FREQUENCY);
}
int entity__getCores() {
	return 0; // was already deprecated in v1
}
ls::LSValue* entity__getCoresEntity(const ls::LSValue*) {
	return ls::LSNumber::get(0); // was already deprecated in v1
}
int entity__getDamageReturn() {
	return Simulator::entity->getDamageReturn();
}
ls::LSValue* entity__getDamageReturnEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::DAMAGE_RETURN);
}
int entity__getMagic() {
	return Simulator::entity->getMagic();
}
ls::LSValue* entity__getMagicEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MAGIC);
}
int entity__getRelativeShield() {
	return Simulator::entity->getRelativeShield();
}
ls::LSValue* entity__getRelativeShieldEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RELATIVE_SHIELD);
}
int entity__getResistance() {
	return Simulator::entity->getResistance();
}
ls::LSValue* entity__getResistanceEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RESISTANCE);
}
int entity__getScience() {
	return Simulator::entity->getScience();
}
ls::LSValue* entity__getScienceEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::SCIENCE);
}
int entity__getStrength() {
	return Simulator::entity->getStrength();
}
ls::LSValue* entity__getStrengthEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::STRENGTH);
}
int entity__getTotalLife() {
	return Simulator::entity->getTotalLife();
}
ls::LSValue* entity__getTotalLifeEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::LIFE);
}
int entity__getTotalMP() {
	return Simulator::entity->getTotalMP();
}
ls::LSValue* entity__getTotalMPEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MP);
}
int entity__getTotalTP() {
	return Simulator::entity->getTotalTP();
}
ls::LSValue* entity__getTotalTPEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::TP);
}
int entity__getWisdom() {
	return Simulator::entity->getWisdom();
}
ls::LSValue* entity__getWisdomEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::WISDOM);
}

int entity__getLife() {
	return Simulator::entity->getLife();
}
ls::LSValue* entity__getLifeEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->life);
}

int entity__getTP() {
	return Simulator::entity->getTP();
}
ls::LSValue* entity__getTPEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getTP());
}

int entity__getMP() {
	return Simulator::entity->getMP();
}
ls::LSValue* entity__getMPEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getMP());
}

int entity__getBirthTurn() {
	return 0;
}
ls::LSValue* entity__getBirthTurnEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(0);
}

int entity__getCell() {
	return Simulator::entity->cell->id;
}
ls::LSValue* entity__getCellEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->cell->id);
}

ls::LSArray<int>* entity__getChips() {
	// TODO Int array
//	return Simulator::entity->chips.clone();
}
ls::LSValue* entity__getChipsEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->chips.clone();
}

ls::LSArray<ls::LSValue*>* entity__getEffects() {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getEffectsEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getEntityTurnOrder() {
	// TODO
}
ls::LSValue* entity__getEntityTurnOrderEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSArray<ls::LSValue*>* entity__getLaunchedEffects() {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getLaunchedEffectsEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLeekID() {
	return Simulator::entity->id;
}
ls::LSValue* entity__getLeekIDEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLevel() {
	return Simulator::entity->level;
}
ls::LSValue* entity__getLevelEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->level);
}

ls::LSString* entity__getName() {
	return new ls::LSString(Simulator::entity->level);
}
ls::LSValue* entity__getNameEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->name);
}

int entity__getNearestEnemy(void*) {
	return Simulator::entity->getClosestEnemy()->id;
}

ls::LSValue* entity__getSummoner() {
	// TODO
}
ls::LSValue* entity__getSummonerEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getTeamID() {
	// TODO
//	return LSNumber::get(e->team_id);
}
ls::LSValue* entity__getTeamIDEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->team_id);
}

/*
 * Null or string
 */
ls::LSValue* entity__getTeamName() {
//	return new LSString(e->team_name);
}
ls::LSValue* entity__getTeamNameEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->team_name);
}

ls::LSValue* entity__getType() {
	// TODO
}
ls::LSValue* entity__getTypeEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getWeapon() {
	// TODO
}
ls::LSValue* entity__getWeaponEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapon->clone();
}

ls::LSArray<int>* entity__getWeapons() {
	// TODO
}
ls::LSValue* entity__getWeaponsEntity(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapons.clone();
}

bool entity__isAlive(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isAlive();
}

bool entity__isDead(const ls::LSValue* entity) {
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isDead();
}

bool entity__isAlly(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isEnemy(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isSummon() {
	// TODO
	return false;
}
bool entity__isSummonEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return false;
	return false;
}

int entity__getLeek() {
	return Simulator::entity->id;
}

ls::LSArray<ls::LSValue*>* entity__listen() {
	// TODO
	return new ls::LSArray<ls::LSValue*>();
}

bool entity__say(const ls::LSValue* message) {
	return Simulator::entity->say(message);
}

bool entity__setWeapon(const ls::LSValue* weapon) {
	// TODO
	// Weapon is an int
	return false;
}

/*
 * Null or int
 */
ls::LSValue* entity__getCooldown(const ls::LSValue* chip) {
	// TODO
}
ls::LSValue* entity__getCooldownEntity(const ls::LSValue* chip, const ls::LSValue* entity) {
	// TODO
}

ls::LSValue* entity__resurrect() {
	// TODO
}
ls::LSValue* entity__summon() {
	// TODO
}
ls::LSValue* entity__useChip() {
	// TODO
}
ls::LSValue* entity__useChipOnCell() {
	// TODO
}
