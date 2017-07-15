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
const ls::Type EntityModule::array_type(ls::RawType::ARRAY, ls::Nature::POINTER, EntityModule::type);

EntityModule::EntityModule() : Module("Entity") {

	EntityModule::entity_clazz = this->clazz;

	field("absoluteShield", ls::Type::INTEGER, (void*) &Entity::getAbsoluteShield);
	field("agility", ls::Type::INTEGER, (void*) &Entity::getAgility);
	field("cell", CellModule::type, (void*) &Entity::getCell);
	field("chips", ChipModule::array_type, (void*) &Entity::getChips);
	field("damageReturn", ls::Type::INTEGER, (void*) &Entity::getDamageReturn);
	field("frequency", ls::Type::INTEGER, (void*) &Entity::getFrequency);
	field("level", ls::Type::INTEGER, (void*) &Entity::getLevel);
	field("life", ls::Type::INTEGER, (void*) &Entity::getLife);
	field("name", ls::Type::STRING, (void*) &Entity::getName);
	field("magic", ls::Type::INTEGER, (void*) &Entity::getMagic);
	field("mp", ls::Type::INTEGER, (void*) &Entity::getMP);
	field("relativeShield", ls::Type::INTEGER, (void*) &Entity::getRelativeShield);
	field("resistance", ls::Type::INTEGER, (void*) &Entity::getResistance);
	field("science", ls::Type::INTEGER, (void*) &Entity::getScience);
	field("strength", ls::Type::INTEGER, (void*) &Entity::getStrength);
	field("talent", ls::Type::INTEGER, (void*) &Entity::getTalent);
	field("totalMP", ls::Type::INTEGER, (void*) &Entity::getTotalMP);
	field("totalTP", ls::Type::INTEGER, (void*) &Entity::getTotalTP);
	field("tp", ls::Type::INTEGER, (void*) &Entity::getTP);
	field("weapon", WeaponModule::type, (void*) &Entity::getWeapon);
	field("weapons", WeaponModule::array_type, (void*) &Entity::getWeapons);
	field("wisdom", ls::Type::INTEGER, (void*) &Entity::getWisdom);

	method("getAliveAllies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_alive_allies, ls::Method::NATIVE}});
	method("getAliveEnemies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_alive_enemies, ls::Method::NATIVE}});
	method("getAllies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_allies, ls::Method::NATIVE}});
	method("getClosestAlly", {{EntityModule::type_ptr, {EntityModule::type_ptr}, (void*) &Entity::get_closest_ally, ls::Method::NATIVE}});
	method("getClosestEnemy", {{EntityModule::type_ptr, {EntityModule::type_ptr}, (void*) &Entity::get_closest_enemy, ls::Method::NATIVE}});
	method("getDeadAllies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_alive_allies, ls::Method::NATIVE}});
	method("getDeadEnemies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_alive_enemies, ls::Method::NATIVE}});
	method("getEnemies", {{EntityModule::array_type, {EntityModule::type_ptr}, (void*) &Entity::get_enemies, ls::Method::NATIVE}});
	method("getFarthestAlly", {{EntityModule::type_ptr, {EntityModule::type_ptr}, (void*) &Entity::get_farthest_ally, ls::Method::NATIVE}});
	method("getFarthestEnemy", {{EntityModule::type_ptr, {EntityModule::type_ptr}, (void*) &Entity::get_farthest_enemy, ls::Method::NATIVE}});
	method("isAlly", {{ls::Type::BOOLEAN, {EntityModule::type_ptr}, (void*) &Entity::isAlly, ls::Method::NATIVE}});
	method("isEnemy", {{ls::Type::BOOLEAN, {EntityModule::type_ptr}, (void*) &Entity::isEnemy, ls::Method::NATIVE}});
	method("moveToward", {
		{ls::Type::INTEGER, {EntityModule::type_ptr, EntityModule::type_ptr, ls::Type::INTEGER}, (void*) &Entity::moveTowardMP, ls::Method::NATIVE},
		{ls::Type::INTEGER, {EntityModule::type_ptr, EntityModule::type_ptr}, (void*) &Entity::moveToward, ls::Method::NATIVE},
		{ls::Type::INTEGER, {EntityModule::type_ptr, CellModule::type, ls::Type::INTEGER}, (void*) &Entity::moveTowardCellMP, ls::Method::NATIVE},
		{ls::Type::INTEGER, {EntityModule::type_ptr, CellModule::type}, (void*) &Entity::moveTowardCell, ls::Method::NATIVE},
	});
	method("useChip", {{ls::Type::INTEGER, {EntityModule::type_ptr, ChipModule::type, EntityModule::type_ptr}, (void*) &Entity::useChip, ls::Method::NATIVE}});
	method("useWeapon", {{ls::Type::INTEGER, {EntityModule::type_ptr, EntityModule::type_ptr}, (void*) &Entity::useWeapon, ls::Method::NATIVE}});
	method("say", {{ls::Type::BOOLEAN, {EntityModule::type_ptr, ls::Type::POINTER}, (void*) &Entity::say, ls::Method::NATIVE}});
	method("setWeapon", {
		{ls::Type::NULLL, {EntityModule::type_ptr, WeaponModule::type}, (void*) &entity_setWeapon, ls::Method::NATIVE},
		{ls::Type::NULLL, {EntityModule::type_ptr, ls::Type::INTEGER}, (void*) &Entity::setWeaponInteger, ls::Method::NATIVE}
	});

	/*
	 * V1 functions
	 */
	method("_getLeek", ls::Method::Static, {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLeek, ls::Method::NATIVE}});

	method("_getAbsoluteShield", ls::Method::Static, {
		{ls::Type::POINTER, {}, (void*) &entity__getAbsoluteShield, ls::Method::NATIVE},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getAbsoluteShieldEntity, ls::Method::NATIVE}
	});
	method("_getAgility", ls::Method::Static, {
		{ls::Type::POINTER, {}, (void*) &entity__getAgility, ls::Method::NATIVE},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getAgilityEntity, ls::Method::NATIVE}
	});
	method("_getBirthTurn", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getBirthTurn},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getBirthTurnEntity}
	});
	method("_getCell", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getCell},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCellEntity}
	});
	method("_getChips", ls::Method::Static, {
		{ls::Type::INT_ARRAY, {}, (void*) &entity__getChips},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getChipsEntity},
	});
	method("_getCores", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getCores},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCoresEntity},
	});
	method("_getDamageReturn", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getDamageReturn},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getDamageReturnEntity}
	});
	method("_getEffects", ls::Method::Static, {
		{ls::Type::PTR_ARRAY, {}, (void*) &entity__getEffects},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getEffectsEntity}
	});
	method("_getEntityTurnOrder", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getEntityTurnOrder},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getEntityTurnOrderEntity}
	});
	method("_getFrequency", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getFrequency},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getFrequencyEntity}
	});
	method("_getLaunchedEffects", ls::Method::Static, {
		{ls::Type::PTR_ARRAY, {}, (void*) &entity__getLaunchedEffects},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLaunchedEffectsEntity}
	});
	method("_getLeekID", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getLeekID},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLeekIDEntity}
	});
	method("_getLevel", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getLevel},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLevelEntity}
	});
	method("_getLife", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getLife},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getLifeEntity}
	});
	method("_getMagic", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getMagic},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getMagicEntity}
	});
	method("_getMP", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getMP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getMPEntity}
	});
	method("_getName", ls::Method::Static, {
		{ls::Type::STRING, {}, (void*) &entity__getName},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getNameEntity}
	});
	method("_getNearestEnemy", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getNearestEnemy}
	});
	method("_getNearestAlly", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getNearestAlly}
	});
	method("_getRelativeShield", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getRelativeShield},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getRelativeShieldEntity}
	});
	method("_getResistance", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getResistance},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getResistanceEntity}
	});
	method("_getScience", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getScience},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getScienceEntity}
	});
	method("_getStrength", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getStrength},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getStrengthEntity}
	});
	method("_getSummoner", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getSummoner},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getSummonerEntity}
	});
	method("_getTeamID", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getTeamID},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTeamIDEntity}
	});
	method("_getTeamName", ls::Method::Static, {
		{ls::Type::STRING, {}, (void*) &entity__getTeamName},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTeamNameEntity}
	});
	method("_getTotalLife", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalLife},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalLifeEntity}
	});
	method("_getTotalMP", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalMP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalMPEntity}
	});
	method("_getTotalTP", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getTotalTP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTotalTPEntity}
	});
	method("_getTP", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getTP},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTPEntity}
	});
	method("_getType", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getType},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getTypeEntity}
	});
	method("_getWeapon", ls::Method::Static, {
		{ls::Type::POINTER, {}, (void*) &entity__getWeapon},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWeaponEntity}
	});
	method("_getWeapons", ls::Method::Static, {
		{ls::Type::INT_ARRAY, {}, (void*) &entity__getWeapons},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWeaponsEntity}
	});
	method("_getWisdom", ls::Method::Static, {
		{ls::Type::INTEGER, {}, (void*) &entity__getWisdom},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getWisdomEntity}
	});
	method("_isAlive", ls::Method::Static, {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isAlive}});
	method("_isAlly", ls::Method::Static, {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isAlly}});
	method("_isDead", ls::Method::Static, {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isDead}});
	method("_isEnemy", ls::Method::Static, {{ls::Type::BOOLEAN, {ls::Type::POINTER}, (void*) &entity__isEnemy}});
	method("_isSummon", ls::Method::Static, {
		{ls::Type::BOOLEAN, {}, (void*) &entity__isSummon},
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__isSummonEntity},
	});

	method("_getCooldown", ls::Method::Static, {
		{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__getCooldown},
		{ls::Type::POINTER, {ls::Type::POINTER, ls::Type::POINTER}, (void*) &entity__getCooldownEntity},
	});

	method("_listen", ls::Method::Static, {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__listen}});
	method("_moveToward", ls::Method::Static, {{ls::Type::INTEGER, {ls::Type::POINTER}, (void*) &entity__moveToward}});
	method("_say", ls::Method::Static, {{ls::Type::POINTER, {ls::Type::POINTER}, (void*) &entity__say}});
	method("_setWeapon", ls::Method::Static, {{ls::Type::BOOLEAN, {ls::Type::NUMBER}, (void*) &entity__setWeapon}});
	method("_useWeapon", ls::Method::Static, {{ls::Type::INTEGER, {ls::Type::NUMBER}, (void*) &entity__useWeapon}});
}

EntityModule::~EntityModule() {}

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
	Entity* e = entity__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->name);
}

int entity__getNearestEnemy(void*) {
	return Simulator::entity->get_closest_enemy()->id;
}
int entity__getNearestAlly(void*) {
	return Simulator::entity->get_closest_ally()->id;
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
