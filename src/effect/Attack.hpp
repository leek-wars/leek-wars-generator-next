#ifndef SRC_EFFECT_ATTACK_HPP_
#define SRC_EFFECT_ATTACK_HPP_

#include <vector>
class Fight;
class Area;
#include "Effect.hpp"
class Cell;
enum class AreaType;

enum AttackResult {
	CRITICAL = 2,
	SUCCESS = 1,
	FAILED = 0,
	INVALID_TARGET = -1,
	NOT_ENOUGH_TP = -2,
	INVALID_COOLDOWN = -3,
	INVALID_POSITION = -4,
	TOO_MANY_SUMMONS = -5,
	RESURRECT_INVALID_ENTIITY = -6
};

enum LaunchType {
	LINE = 0,
	CIRCLE = 1
};

enum class AttackType {
	WEAPON = 1,
	CHIP = 2
};

struct EffectParameters {
	EffectType type;
	double value1;
	double value2;
	int turns;
	int targets;
	bool stackable;
};

class Attack {
public:

	int min_range;
	int max_range;
	bool need_los;
	LaunchType launch_type;
	std::unique_ptr<Area> area;
	AttackType attack_type;
	std::vector<EffectParameters> effects;

	int healAttack = 0;
	int dammageAttack = 0;

	Attack(int min_range, int max_range, LaunchType launchType, AreaType area_type, bool los, std::vector<EffectParameters> effects, AttackType attack_type);
	virtual ~Attack();

	const EffectParameters* getEffectParametersByType(const EffectType type) const;

	std::vector<Entity*> applyOnCell(Fight* fight, Entity* caster, Cell* target, int item_id, bool critical) const;

	bool filterTarget(int targets, Entity* caster, Entity* target) const;

	double getPowerForCell(Cell* launch_cell, Cell* target_cell, Cell* curent_cell) const;

	static Area* getArea(Attack* attack, AreaType type);
};

#endif /* SRC_EFFECT_ATTACK_HPP_ */
