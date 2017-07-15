#ifndef ENTITY_ENTITY_HPP_
#define ENTITY_ENTITY_HPP_

#include <vector>
#include <string>
#include <ostream>
#include <leekscript.h>
#include "../field/Cell.hpp"
#include "../ai/AI.hpp"
#include "Characteristics.hpp"
#include "../item/Chip.hpp"
#include "../item/Weapon.hpp"
#include "../module/EntityModule.hpp"
class Fight;
class Effect;
class Team;

enum class Characteristic {
	LIFE, TP, MP, STRENGTH, AGILITY, FREQUENCY, WISDOM, ABSOLUTE_SHIELD, RELATIVE_SHIELD,
	RESISTANCE, SCIENCE, MAGIC, DAMAGE_RETURN
};

class Entity : public ls::LSObject {
public:

	static int next_id;

	Fight* fight;

	int id;
	std::string name;

	Cell* cell;
	Cell* start_cell;
	Characteristics base_characs;
	Characteristics bonus_characs;
	int total_life;

	int level;
	int talent;

	int farmer;
	std::string farmer_name;
	int team_id;
	std::string team_name = "";

	// Current effects on the entity
	ls::LSArray<LSValue*> effects;

	// Effects created by the entity
	ls::LSArray<LSValue*> launched_effects;

	// Current cooldowns of the entity
	std::map<int, int> cooldowns;

	Team* team;

	std::unique_ptr<AI> ai;

	ls::LSArray<LSValue*> chips;
	ls::LSArray<LSValue*> weapons;

	const Weapon* weapon;
	int used_tp;
	int used_mp;
	int life;
	bool has_moved = false;

	// TODO registers
	// private Register mRegister = null;

	std::ostringstream* debug_output;
	size_t log_length = 0;

	Entity(Fight* fight, std::string name, int level);
	virtual ~Entity();

	/*
	 * General information
	 */
	bool isAlive() const;
	bool isDead() const;
	bool isAlly() const;
	bool isEnemy() const;
	bool isSummon() const;
	void setCell(Cell* cell);
	Cell* getCell();
	int getLevel() const;
	ls::LSString* getName() const;
	int getTalent() const;

	/*
	 * Items
	 */
	void setWeapons(std::vector<Weapon*> weapons);
	const Weapon* getWeapon();
	ls::LSArray<ls::LSValue*>* getWeapons();
	bool setWeapon(const Weapon* weapon);
	bool setWeaponInteger(int weapon);
	void setChips(std::vector<Chip*> chips);
	ls::LSArray<ls::LSValue*>* getChips();

	/*
	 * Characteristics
	 */
 	void addLife(int l);
 	void removeLife(int life, Entity* attacker);
	void setCharacteristics(Characteristics characs);
	int getCharacteristic(Characteristic characteristic) const;
	void updateCharacteristics();
	void updateBonusCharacteristics();
	void updateBonusCharacteristics(Characteristic charac);
	int getTP() const;
	int getMP() const;
	int getTotalTP() const;
	int getTotalMP() const;
	int getLife() const;
	int getTotalLife() const;
	int getStrength() const;
	int getScience() const;
	int getMagic() const;
	int getWisdom() const;
	int getFrequency() const;
	int getAgility() const;
	int getResistance() const;
	int getDamageReturn() const;
	int getAbsoluteShield() const;
	int getRelativeShield() const;

	/*
	 * Fight actions
	 */
	void useTP(int tp);
	void useMP(int mp);
	void endTurn();
	int move(const std::vector<const Cell*> path);
	int moveToward(Entity* target);
	int moveTowardMP(Entity* target, int max_mp);
	int moveTowardCell(Cell* target);
	int moveTowardCellMP(Cell* target, int max_mp);
	int useChip(Chip* chip, Entity* target);
	int useChipOnCell(Chip* chip, Cell* cell);
	int useWeapon(Entity* target);
	int useWeaponOnCell(Cell* cell);
	void addCooldown(Chip* chip, int cooldown);
	bool hasCooldown(int chipID) const;
	int getCooldown(int chipID);
	bool say(const ls::LSValue* message);

	/*
	 * Effects management
	 */
	ls::LSArray<ls::LSValue*> getEffects();
	ls::LSArray<ls::LSValue*> getLaunchedEffects();
	void addEffect(Effect* effect);
	void addLaunchedEffect(Effect* effect);
	void removeEffect(Effect* effect);
	void remove_launched_effect(Effect* effect);
	void clear_poisons();

	/*
	 * Entity getters
	 */
	ls::LSArray<ls::LSValue*> get_enemies() const;
	ls::LSArray<ls::LSValue*> get_allies() const;
	ls::LSArray<ls::LSValue*> get_alive_enemies() const;
	ls::LSArray<ls::LSValue*> get_alive_allies() const;
	ls::LSArray<ls::LSValue*> get_dead_enemies() const;
	ls::LSArray<ls::LSValue*> get_dead_allies() const;
	Entity* get_closest(ls::LSArray<ls::LSValue*> entities) const;
	Entity* get_closest_enemy() const;
	Entity* get_closest_ally() const;
	Entity* get_farthest(ls::LSArray<ls::LSValue*> entities) const;
	Entity* get_farthest_enemy() const;
	Entity* get_farthest_ally() const;

	/*
	 * LeekScript overrides
	 */
	virtual ls::LSValue* getClass() const override;
	virtual std::ostream& print(std::ostream& os) const override;
	virtual std::ostream& dump(std::ostream& os, int level) const override;

	/*
	 * Export to JSON format
	 */
	Json to_json() const;
};

#endif
