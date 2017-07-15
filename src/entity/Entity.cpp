#include <algorithm>
#include "Entity.hpp"
#include "../field/Field.hpp"
#include "../module/WeaponModule.hpp"
#include "../fight/Fight.hpp"
#include "../action/ActionLoseTP.hpp"
#include "../action/ActionLoseMP.hpp"
#include "../action/ActionSay.hpp"
#include "../action/ActionSetWeapon.hpp"
#include "Team.hpp"
#include "../fight/Simulator.hpp"
#include <leekscript.h>
#include "../util/Util.hpp"
#include "../action/ActionLoseMP.hpp"
#include "../action/ActionMove.hpp"

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
	team_id = 1212;
	talent = 1000;
	cell = nullptr;

	auto name_val = new ls::LSString(name);
	name_val->native = true;
	name_val->refs = 1;
	addField("name", name_val);
	addField("cell", ls::LSNull::get());
	weapons.refs = 10;

	debug_output = new std::ostringstream();
}

Entity::~Entity() {
	delete values["name"];
	values.erase("name");
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
	values["weapons"] = &this->weapons;
}

void Entity::setChips(std::vector<Chip*> chips) {
	this->chips = std::vector<ls::LSValue*>(chips.begin(), chips.end());
	this->chips.native = true;
	this->chips.refs = 1;
	values["chips"] = &this->chips;
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

void Entity::updateBonusCharacteristics() {
	bonus_characs.clear();
	for (auto& v : effects) {
		auto effect = (Effect*) v;
		bonus_characs.add(effect->characs);
	}
}

void Entity::updateBonusCharacteristics(Characteristic charac) {
	bonus_characs.set(charac, 0);
	for (auto& v : effects) {
		auto effect = (Effect*) v;
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
int Entity::getTalent() const {
	return 1000;
}

int Entity::move(const std::vector<const Cell*> path) {

	int size = path.size();
	if (size == 0 or size > getMP()) {
		return 0;
	}
	fight->actions.add(new ActionMove(this, path));
	fight->actions.add(new ActionLoseMP(this, size));

	// TODO Statistics and trophy manager
	// trophyManager.deplacement(entity.getFarmer(), path);

	useMP(size);
	has_moved = true;
	// Clear previous cell
	cell->setEntity(nullptr);
	// Set new cell
	((Cell*) path[path.size() - 1])->setEntity(this);
	return path.size();
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

Entity* Entity::get_closest(ls::LSArray<ls::LSValue*> entities) const {
	if (entities.size() == 0) {
		return nullptr;
	}
	Entity* closest = nullptr;
	int min_distance = std::numeric_limits<int>::max();
	for (auto& entity : entities) {
		if (entity == this) continue;
		int distance = cell->distance(((Entity*) entity)->cell);
		if (distance < min_distance) {
			min_distance = distance;
			closest = (Entity*) entity;
		}
	}
	return closest;
}

Entity* Entity::get_farthest(ls::LSArray<ls::LSValue*> entities) const {
	if (entities.size() == 0) {
		return nullptr;
	}
	Entity* farthest = nullptr;
	int max_distance = std::numeric_limits<int>::max();
	for (auto& entity : entities) {
		if (entity == this) continue;
		int distance = cell->distance(((Entity*) entity)->cell);
		if (distance > max_distance) {
			max_distance = distance;
			farthest = (Entity*) entity;
		}
	}
	return farthest;
}

ls::LSArray<ls::LSValue*> Entity::get_enemies() const {
	ls::LSArray<ls::LSValue*> enemies;
	for (const auto& team : fight->teams) {
		if (team != this->team) {
			enemies.insert(enemies.end(), team->entities.begin(), team->entities.end());
		}
	}
	return enemies;
}

ls::LSArray<ls::LSValue*> Entity::get_allies() const {
	return std::vector<ls::LSValue*>(team->entities.begin(), team->entities.end());
}

ls::LSArray<ls::LSValue*> Entity::get_alive_enemies() const {
	ls::LSArray<ls::LSValue*> enemies;
	for (const auto& team : fight->teams) {
		if (team == this->team) continue;
		for (const auto& entity : team->entities) {
			if (entity->isAlive()) {
				enemies.push_back(entity);
			}
		}
	}
	return enemies;
}

ls::LSArray<ls::LSValue*> Entity::get_alive_allies() const {
	ls::LSArray<ls::LSValue*> allies;
	for (const auto& entity : team->entities) {
		if (entity->isAlive()) {
			allies.push_back(entity);
		}
	}
	return allies;
}

ls::LSArray<ls::LSValue*> Entity::get_dead_enemies() const {
	ls::LSArray<ls::LSValue*> enemies;
	for (const auto& team : fight->teams) {
		if (team == this->team) continue;
		for (const auto& entity : team->entities) {
			if (entity->isAlive()) {
				enemies.push_back(entity);
			}
		}
	}
	return enemies;
}

ls::LSArray<ls::LSValue*> Entity::get_dead_allies() const {
	ls::LSArray<ls::LSValue*> allies;
	for (const auto& entity : team->entities) {
		if (entity->isDead()) {
			allies.push_back(entity);
		}
	}
	return allies;
}

Entity* Entity::get_closest_enemy() const {
	return get_closest(get_enemies());
}

Entity* Entity::get_closest_ally() const {
	return get_closest(get_allies());
}

Entity* Entity::get_farthest_enemy() const {
	return get_farthest(get_enemies());
}

Entity* Entity::get_farthest_ally() const {
	return get_farthest(get_allies());
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
	std::ostringstream oss;
	message->print(oss);

	std::string msg = oss.str();

	if (msg.size() > 500) {
		msg = msg.substr(0, 500);
	}

	// TODO Censor say string
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

	LOG << name << " (" << id << ") move toward " << target->name << " (" << target->id << ")" << std::endl;

	if (target == nullptr or target->isDead()) return 0;

	return moveTowardCellMP(target->cell, max_mp);
}

int Entity::moveTowardCell(Cell* target) {
	return moveTowardCellMP(target, getMP());
}

int Entity::moveTowardCellMP(Cell* target, int max_mp) {

	LOG << name << " (" << id << ") move toward " << target->id << std::endl;

	if (max_mp <= 0 or getMP() <= 0) return 0;

	int mp = max_mp == -1 ? getMP() : std::min(getMP(), max_mp);

	auto path = fight->field->get_path_between(cell, target, {});
	if (path.size() == 0) {
		return 0;
	}
	return move({path.begin() + 1, path.begin() + std::min((int) path.size(), mp + 1)});
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
	// TODO Add ActionRemoveEffect action
	// fight.log(new ActionRemoveEffect(effect.getLogID()));
	effects.erase(std::find(effects.begin(), effects.end(), effect));
	updateBonusCharacteristics();
}

void Entity::remove_launched_effect(Effect* effect) {
	auto it = std::find(launched_effects.begin(), launched_effects.end(), effect);
	if (it != launched_effects.end()) {
		launched_effects.erase(it);
	}
}

void Entity::clear_poisons() {
	for (size_t i = 0; i < effects.size(); ++i) {
		auto effect = (Effect*) effects[i];
		if (effect->type == EffectType::POISON) {
			effect->caster->remove_launched_effect(effect);
			removeEffect(effect);
			i--;
		}
	}
}

ls::LSValue* Entity::getClass() const {
	return (ls::LSValue*) EntityModule::entity_clazz;
}

std::ostream& Entity::print(std::ostream& os) const {
	os << "<Entity " << name << ">";
	return os;
}

std::ostream& Entity::dump(std::ostream& os, int) const {
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
