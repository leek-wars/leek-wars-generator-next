#include "EntityModule.hpp"

#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* EntityModule::entity_clazz;
const EntityType* const EntityModule::type = new EntityType();
const ls::Type EntityModule::type_ptr(EntityModule::type, ls::Nature::POINTER, true);

EntityModule::EntityModule() : Module("Entity") {

	EntityModule::entity_clazz = this->clazz;

	field("name", Type::STRING);
	field("cell", CellModule::type);
	field("level", Type::INTEGER_P);
	field("talent", Type::INTEGER_P);

	field("life", Type::INTEGER_P);
	field("strength", Type::INTEGER_P);
	field("agility", Type::INTEGER_P);
	field("science", Type::INTEGER_P);
	field("resistance", Type::INTEGER_P);
	field("magic", Type::INTEGER_P);
	field("frequency", Type::INTEGER_P);
	field("tp", Type::INTEGER_P);
	field("mp", Type::INTEGER_P);
	field("relativeShield", Type::INTEGER_P);
	field("absoluteShield", Type::INTEGER_P);
	field("totalTP", Type::INTEGER_P);
	field("totalMP", Type::INTEGER_P);
	field("damageReturn", Type::INTEGER_P);

	method("getLife", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getLife);
	method("getTotalLife", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getStrength);
	method("getStrength", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getStrength);
	method("getAgility", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getAgility);
	method("getScience", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getScience);
	method("getMagic", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getMagic);
	method("getWisdom", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getWisdom);
	method("getFrequency", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getFrequency);
	method("getResistance", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getResistance);
	method("getTP", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getTP);
	method("getRelativeShield", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getRelativeShield);
	method("getAbsoluteShield", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getAbsoluteShield);
	method("getTotalTP", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getTotalTP);
	method("getTotalMP", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getTotalMP);
	method("getDamageReturn", EntityModule::type_ptr, Type::INTEGER, {}, (void*) &Entity::getDamageReturn);
	method("getCell", EntityModule::type_ptr, CellModule::type, {}, (void*) &Entity::getCell);
	method("getClosestEnemy", EntityModule::type_ptr, EntityModule::type_ptr, {}, (void*) &entity_getClosestEnemy);
	method("getWeapons", EntityModule::type_ptr, WeaponModule::array_type, {}, (void*) &Entity::getWeapons);
	method("getWeapon", EntityModule::type_ptr, WeaponModule::type, {}, (void*) &Entity::getWeapon);

	method("setWeapon", {
		{EntityModule::type_ptr, Type::NULLL, {WeaponModule::type}, (void*) &entity_setWeapon},
		{EntityModule::type_ptr, Type::NULLL, {Type::INTEGER}, (void*) &Entity::setWeaponInteger}
	});

	method("useChip", EntityModule::type_ptr, Type::INTEGER, {ChipModule::type, EntityModule::type_ptr}, (void*) &Entity::useChip);

	method("useWeapon", EntityModule::type_ptr, Type::INTEGER, {EntityModule::type_ptr}, (void*) &Entity::useWeapon);

	method("getChips", EntityModule::type_ptr, ChipModule::array_type, {}, (void*) &Entity::getChips);

	method("say", EntityModule::type_ptr, Type::NULLL, {Type::POINTER}, (void*) &Entity::say);

	method("moveToward", EntityModule::type_ptr, Type::INTEGER, {EntityModule::type_ptr, Type::INTEGER}, (void*) &Entity::moveToward);

	/*
	 * V1 functions
	 */
	static_method("_getLeek", Type::POINTER, {Type::POINTER}, (void*) &entity__getLeek);

	static_method("_getAbsoluteShield", {
		{Type::POINTER, {}, (void*) &entity__getAbsoluteShield},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getAbsoluteShieldEntity}
	});
	static_method("_getAgility", {
		{Type::POINTER, {}, (void*) &entity__getAgility},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getAgilityEntity}
	});
	static_method("_getBirthTurn", {
		{Type::INTEGER, {}, (void*) &entity__getBirthTurn},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getBirthTurnEntity}
	});
	static_method("_getCell", {
		{Type::INTEGER, {}, (void*) &entity__getCell},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getCellEntity}
	});
	static_method("_getChips", {
		{Type::INT_ARRAY, {}, (void*) &entity__getChips},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getChipsEntity},
	});
	static_method("_getCores", {
		{Type::INTEGER, {}, (void*) &entity__getCores},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getCoresEntity},
	});
	static_method("_getDamageReturn", {
		{Type::INTEGER, {}, (void*) &entity__getDamageReturn},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getDamageReturnEntity}
	});
	static_method("_getEffects", {
		{Type::PTR_ARRAY, {}, (void*) &entity__getEffects},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getEffectsEntity}
	});
	static_method("_getEntityTurnOrder", {
		{Type::INTEGER, {}, (void*) &entity__getEntityTurnOrder},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getEntityTurnOrderEntity}
	});
	static_method("_getFrequency", {
		{Type::INTEGER, {}, (void*) &entity__getFrequency},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getFrequencyEntity}
	});
	static_method("_getLaunchedEffects", {
		{Type::PTR_ARRAY, {}, (void*) &entity__getLaunchedEffects},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getLaunchedEffectsEntity}
	});
	static_method("_getLeekID", {
		{Type::INTEGER, {}, (void*) &entity__getLeekID},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getLeekIDEntity}
	});
	static_method("_getLevel", {
		{Type::INTEGER, {}, (void*) &entity__getLevel},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getLevelEntity}
	});
	static_method("_getLife", {
		{Type::INTEGER, {}, (void*) &entity__getLife},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getLifeEntity}
	});
	static_method("_getMagic", {
		{Type::INTEGER, {}, (void*) &entity__getMagic},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getMagicEntity}
	});
	static_method("_getMP", {
		{Type::INTEGER, {}, (void*) &entity__getMP},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getMPEntity}
	});
	static_method("_getName", {
		{Type::STRING, {}, (void*) &entity__getName},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getNameEntity}
	});
	static_method("_getRelativeShield", {
		{Type::INTEGER, {}, (void*) &entity__getRelativeShield},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getRelativeShieldEntity}
	});
	static_method("_getResistance", {
		{Type::INTEGER, {}, (void*) &entity__getResistance},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getResistanceEntity}
	});
	static_method("_getScience", {
		{Type::INTEGER, {}, (void*) &entity__getScience},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getScienceEntity}
	});
	static_method("_getStrength", {
		{Type::INTEGER, {}, (void*) &entity__getStrength},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getStrengthEntity}
	});
	static_method("_getSummoner", {
		{Type::INTEGER, {}, (void*) &entity__getSummoner},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getSummonerEntity}
	});
	static_method("_getTeamID", {
		{Type::INTEGER, {}, (void*) &entity__getTeamID},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTeamIDEntity}
	});
	static_method("_getTeamName", {
		{Type::STRING, {}, (void*) &entity__getTeamName},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTeamNameEntity}
	});
	static_method("_getTotalLife", {
		{Type::INTEGER, {}, (void*) &entity__getTotalLife},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTotalLifeEntity}
	});
	static_method("_getTotalMP", {
		{Type::INTEGER, {}, (void*) &entity__getTotalMP},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTotalMPEntity}
	});
	static_method("_getTotalTP", {
		{Type::INTEGER, {}, (void*) &entity__getTotalTP},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTotalTPEntity}
	});
	static_method("_getTP", {
		{Type::INTEGER, {}, (void*) &entity__getTP},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTPEntity}
	});
	static_method("_getType", {
		{Type::INTEGER, {}, (void*) &entity__getType},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getTypeEntity}
	});
	static_method("_getWeapon", {
		{Type::POINTER, {}, (void*) &entity__getWeapon},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getWeaponEntity}
	});
	static_method("_getWeapons", {
		{Type::INT_ARRAY, {}, (void*) &entity__getWeapons},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getWeaponsEntity}
	});
	static_method("_getWisdom", {
		{Type::INTEGER, {}, (void*) &entity__getWisdom},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getWisdomEntity}
	});
	static_method("_isAlive", Type::BOOLEAN, {Type::POINTER}, (void*) &entity__isAlive);
	static_method("_isAlly", Type::BOOLEAN, {Type::POINTER}, (void*) &entity__isAlly);
	static_method("_isDead", Type::BOOLEAN, {Type::POINTER}, (void*) &entity__isDead);
	static_method("_isEnemy", Type::BOOLEAN, {Type::POINTER}, (void*) &entity__isEnemy);
	static_method("_isSummon", {
		{Type::BOOLEAN, {}, (void*) &entity__isSummon},
		{Type::POINTER, {Type::POINTER}, (void*) &entity__isSummonEntity},
	});

	static_method("_getCooldown", {
		{Type::POINTER, {Type::POINTER}, (void*) &entity__getCooldown},
		{Type::POINTER, {Type::POINTER, Type::POINTER}, (void*) &entity__getCooldownEntity},
	});

	static_method("_listen", Type::POINTER, {Type::POINTER}, (void*) &entity__listen);
	static_method("_say", Type::POINTER, {Type::POINTER}, (void*) &entity__say);
	static_method("_setWeapon", Type::POINTER, {Type::POINTER}, (void*) &entity__setWeapon);


}

EntityModule::~EntityModule() {}

const Entity* entity_getClosestEnemy(Entity* entity) {
	return Simulator::fight->teams[(entity->team + 1) % 2]->entities[0];
}

const Weapon* entity_getWeapon(Entity* entity) {
	return (Weapon*) entity->getWeapon();
}

const ls::LSArray<Weapon*>* entity_getWeapons(Entity* entity) {
	return (const ls::LSArray<Weapon*>*) entity->values["weapons"];
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
