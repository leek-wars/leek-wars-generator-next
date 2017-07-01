#include <algorithm>

#include "Entity.hpp"
#include "../map/Map.hpp"
#include "../module/WeaponModule.hpp"
#include "../fight/Fight.hpp"
#include "../action/ActionLoseTP.hpp"
#include "../action/ActionLoseMP.hpp"
#include "../action/ActionSay.hpp"
#include "../action/ActionSetWeapon.hpp"
#include "Team.hpp"
#include "../fight/Simulator.hpp"
#include <leekscript/src/leekscript.h>

int Entity::next_id = 0;

Entity::Entity(Fight* fight, std::string name, int level)
	: fight(fight), name(name), level(level) {

	native = true;
	refs = 1;

	id = Entity::next_id++;
	ai = nullptr;
	used_mp = 0;
	used_tp = 0;
	weapon = nullptr;
	farmer = -1;
	life = 0;
	total_life = 0;
	team = -1;
	team_id = 1212;
	talent = 1000;
	cell = nullptr;

	auto name_val = new ls::LSString(name);
	name_val->native = true;
	name_val->refs = 1;
	addField("name", name_val);
	addField("cell", ls::LSNull::get());
	weapons.refs = 10;
}

Entity::~Entity() {
	delete values["name"];
	values.erase("name");
}

int Entity::getTeam() const {
	return team;
}

bool Entity::isAlive() const {
	return life > 0;
}

bool Entity::isDead() const {
	return life <= 0;
}

bool Entity::isAlly() const {
	return Simulator::entity->team == team;
}

bool Entity::isEnemy() const {
	return Simulator::entity->team != team;
}

bool Entity::isSummon() const {
	return false;
}

void Entity::removeLife(int l, Entity* attacker) {
	if (l > life) {
		l = life;
	}
	life -= l;

	fight->statistics.add_damage(attacker, l, this);

	if (life <= 0) {
		// TODO
		// fight.onPlayerDie(this, attacker);
		// die();
	}
}

void Entity::addLife(int l) {
	if (l > getTotalLife() - life) {
		l = getTotalLife() - life;
	}
	// TODO
	// FightStatistics.addHeal(pv);
	life += l;
}

void Entity::setCell(Cell* cell) {
	//cout << "set cell " << endl;
	if (this->cell == nullptr) {
		this->start_cell = cell;
	}
	this->cell = cell;
	values["cell"] = (Cell*) cell;
	values["cell"]->native = true;
	values["cell"]->refs = 1;
}

Cell* Entity::getCell() {
	return cell;
}

void Entity::setWeapons(std::vector<Weapon*> weapons) {
	this->weapons = std::vector<ls::LSValue*>(weapons.begin(), weapons.end());
	this->weapons.native = true;
	this->weapons.refs = 1;
}

void Entity::setChips(std::vector<Chip*> chips) {
	this->chips = std::vector<ls::LSValue*>(chips.begin(), chips.end());
	this->chips.native = true;
	this->chips.refs = 1;
}

const Weapon* Entity::getWeapon() {
	return this->weapon == nullptr ? (Weapon*)ls::LSNull::get() : this->weapon;
}

ls::LSArray<ls::LSValue*>* Entity::getWeapons() {
	return &this->weapons;
}

bool Entity::setWeapon(const Weapon* weapon) {
	if (getTP() < 1) {
		return false;
	}
	this->weapon = weapon;
	useTP(1);
	fight->actions.add(new ActionSetWeapon(this, weapon));
	return true;
}

bool Entity::setWeaponInteger(int weapon) {
	for (LSValue* v : weapons) {
		Weapon* w = (Weapon*) v;
		if (w->id == weapon) {
			return setWeapon(w);
		}
	}
	return false;
}

ls::LSArray<ls::LSValue*>* Entity::getChips() {
	return &this->chips;
}

void Entity::setCharacteristics(Characteristics characs) {
	base_characs = characs;
	updateCharacteristics();
	total_life = characs.get(Characteristic::LIFE);
	life = total_life;
}

void Entity::updateCharacteristics() {
	values["life"] = ls::LSNumber::get(getLife());
	values["strength"] = ls::LSNumber::get(getStrength());
}

void Entity::updateBonusCharacteristics(Characteristic charac) {
	bonus_characs.set(charac, 0);
	for (LSValue* v : effects) {
		Effect* effect = (Effect*) v;
		bonus_characs.add(charac, effect->characs.get(charac));
	}
}

int Entity::getTP() const {
	return getCharacteristic(Characteristic::TP) - used_tp;
}

int Entity::getMP() const {
	return getCharacteristic(Characteristic::MP) - used_mp;
}

int Entity::getLife() const {
	return life;
}

int Entity::getTotalLife() const {
	return getCharacteristic(Characteristic::LIFE);
}

int Entity::getResistance() const {
	return getCharacteristic(Characteristic::RESISTANCE);
}

int Entity::getFrequency() const {
	return getCharacteristic(Characteristic::FREQUENCY);
}

int Entity::getStrength() const {
	return getCharacteristic(Characteristic::STRENGTH);
}

int Entity::getWisdom() const {
	return getCharacteristic(Characteristic::WISDOM);
}

int Entity::getAgility() const {
	return getCharacteristic(Characteristic::AGILITY);
}

int Entity::getScience() const {
	return getCharacteristic(Characteristic::SCIENCE);
}

int Entity::getMagic() const {
	return getCharacteristic(Characteristic::MAGIC);
}

int Entity::getTotalTP() const {
	return getCharacteristic(Characteristic::TP);
}

int Entity::getTotalMP() const {
	return getCharacteristic(Characteristic::MP);
}

int Entity::getDamageReturn() const {
	return getCharacteristic(Characteristic::DAMAGE_RETURN);
}

int Entity::getAbsoluteShield() const {
	return getCharacteristic(Characteristic::ABSOLUTE_SHIELD);
}

int Entity::getRelativeShield() const {
	return getCharacteristic(Characteristic::RELATIVE_SHIELD);
}

int Entity::getCharacteristic(Characteristic characteristic) const {
	return base_characs.get(characteristic) + bonus_characs.get(characteristic);
}

int Entity::getLevel() const {
	return level;
}

ls::LSString* Entity::getName() const {
	return (ls::LSString*) ((Entity*) this)->values["name"];
}

int Entity::useChip(Chip* chip, Entity* target) {
	if (chip == nullptr or target == nullptr) {
		return -1;
	}
	return fight->useChip(this, target->cell, chip);
}

int Entity::useChipOnCell(Chip* chip, Cell* cell) {
	if (chip == nullptr or cell == nullptr) {
		return -1;
	}
	return fight->useChip(this, cell, chip);
}

int Entity::useWeapon(Entity* target) {
	if (weapon == nullptr or target == nullptr) {
		return -1;
	}
	return fight->useWeapon(this, target->cell);
}

int Entity::useWeaponOnCell(Cell* cell) {
	if (weapon == nullptr or cell == nullptr) {
		return -1;
	}
	return fight->useWeapon(this, cell);
}

Entity* Entity::getClosestEnemy() const {
	// TODO
	return fight->teams[(team + 1) % 2]->entities[0];
}

void Entity::useTP(int tp) {
	used_tp += tp;
	fight->actions.add(new ActionLoseTP(this, tp));
}

void Entity::useMP(int mp) {
	used_mp += mp;
	fight->actions.add(new ActionLoseMP(this, mp));
}

void Entity::endTurn() {
	used_tp = 0;
	used_mp = 0;
}

bool Entity::say(const LSValue* message) {

	if (getTP() < 1) {
		ls::LSValue::delete_temporary(message);
		return false;
	}
	ostringstream oss;
	message->print(oss);

	string msg = oss.str();

	if (msg.size() > 500) {
		msg = msg.substr(0, 500);
	}

	// TODO
	// msg = Censorship.checkString(message);

	fight->actions.add(new ActionSay(this, msg));
	useTP(1);
	ls::LSValue::delete_temporary(message);
	return true;
}

int Entity::moveToward(Entity* target) {
	return moveTowardMP(target, getMP());
}

int Entity::moveTowardMP(Entity* target, int max_mp) {

	cout << "move toward " << target->id << "(me: " << id << ")" << endl;

	if (target == nullptr or target->isDead()) return 0;
	if (max_mp <= 0 or getMP() <= 0) return 0;

	int mp = max_mp == -1 ? getMP() : min(getMP(), max_mp);

	std::cout << "path between " << cell->id << " and " << target->cell->id << std::endl;

	vector<const Cell*> path = fight->map->get_path_between(target->cell, cell, vector<const Cell*> {});

	cout << "path: " << path.size() << endl;

//	return fight.moveEntity(this, path.size() > pm ? path.subList(0, pm) : path);
	if (path.size() == 0) {
		return 0;
	}
	return fight->moveEntity(this, {path.begin() + 1, path.begin() + min((int) path.size(), mp + 1)} );
//	return 0;
}

void Entity::addCooldown(Chip* chip, int cooldown) {
	cooldowns[chip->id] = cooldown == -1 ? Fight::MAX_TURNS + 2 : cooldown;
}

// Entity has cooldown for this chip?
bool Entity::hasCooldown(int chipID) const {
	return cooldowns.find(chipID) != cooldowns.end();
}

// Get current cooldown for a chip
int Entity::getCooldown(int chipID) {
	if (!hasCooldown(chipID)) {
		return 0;
	}
	return cooldowns[chipID];
}

ls::LSArray<ls::LSValue*> Entity::getEffects() {
	return effects;
}

ls::LSArray<ls::LSValue*> Entity::getLaunchedEffects() {
	return launched_effects;
}

void Entity::addEffect(Effect* effect) {
	effects.push_back(effect);
}

void Entity::addLaunchedEffect(Effect* effect) {
	launched_effects.push_back(effect);
}

void Entity::removeEffect(Effect* effect) {

	// TODO
	//fight.log(new ActionRemoveEffect(effect.getLogID()));

//	effects.remove(effect);
	effects.erase(std::find(effects.begin(), effects.end(), effect));

	// updateBuffStats();
}

ls::LSValue* Entity::getClass() const {
	return (ls::LSValue*) EntityModule::entity_clazz;
}

std::ostream& Entity::print(std::ostream& os) const {
	os << "<Entity " << name << ">";
	return os;
}

Json Entity::to_json() const {
	Json json;
	json["id"] = id;
	json["life"] = life;
	json["tp"] = getTotalTP();
	json["mp"] = getTotalMP();
	json["name"] = name;
	json["team"] = team + 1;
	json["cellPos"] = start_cell->id;
	json["appearence"] = 11;
	json["skin"] = 9;
	json["level"] = level;
	json["type"] = 0;
	json["strength"] = getStrength();
	json["agility"] = getAgility();
	json["resistance"] = getResistance();
	json["magic"] = getMagic();
	json["science"] = getScience();
	json["frequency"] = getFrequency();
	json["wisdom"] = getWisdom();
	json["summon"] = false;
	return json;
}
