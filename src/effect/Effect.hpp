#ifndef EFFECT_HPP_
#define EFFECT_HPP_

#include <leekscript.h>
class Fight;
class Entity;
#include "../entity/Characteristics.hpp"
enum class AttackType;

enum class EffectType {
	DAMAGE = 1,
	HEAL = 2,
	BUFF_STRENGTH = 3,
	BUFF_AGILITY = 4,
	RELATIVE_SHIELD = 5,
	ABSOLUTE_SHIELD = 6,
	BUFF_MP = 7,
	BUFF_TP = 8,
	DEBUFF = 9,
	TELEPORT = 10,
	PERMUTATION = 11,
	VITALITY = 12,
	POISON = 13,
	SUMMON = 14,
	RESURRECT = 15,
	KILL = 16,
	SHACKLE_MP = 17,
	SHACKLE_TP = 18,
	SHACKLE_STRENGTH = 19,
	DAMAGE_RETURN = 20,
	BUFF_RESISTANCE = 21,
	BUFF_WISDOM = 22,
	ANTIDOTE = 23,
	SHACKLE_MAGIC = 24,
	AFTEREFFECT = 25,
	VULNERABILITY = 26
};

enum EffectTarget {
	ENEMIES = 1, // Enemies
	ALLIES = 2, // Allies
	CASTER = 4, // Caster
	NON_SUMMONS = 8, // Non-summons
	SUMMONS = 16 // Summons
};

#define CRITICAL_POWER 1.4

class Effect : public ls::LSObject {
public:

	EffectType type;
	int turns = 0;
	double power = 1.0;
	double value1;
	double value2;
	bool critical = false;
	double critical_power = 1.0;
	Entity* caster;
	Entity* target;
	AttackType attackType;
	int attackID;
	double jet;
	Characteristics characs;
	int id = 0;

	Effect();
	virtual ~Effect();

	// Abstract methods
	virtual void apply(Fight* fight);
	virtual void applyStartTurn(Fight* fight);
	virtual int getEffectValue() const;
	virtual bool stackable() const;

	static Effect* construct(EffectType type);
	static void createEffect(Fight* fight, EffectType id, int turns, double power, double value1, double value2, bool critical, Entity* target, Entity* caster, AttackType attack_type, int attack_id, double jet);
};

#endif
