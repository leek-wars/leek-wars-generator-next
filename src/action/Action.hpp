#ifndef ACTION_HPP
#define ACTION_HPP

#include "../../lib/json.hpp"

enum class ActionType {
	START_FIGHT = 0,
	USE_WEAPON = 1,
	USE_CHIP = 2,
	SET_WEAPON = 3,
	END_FIGHT = 4,
	PLAYER_DEAD = 5,
	NEW_TURN = 6,
	LEEK_TURN = 7,
	END_TURN = 8,
	SUMMON = 9,
	MOVE_TO = 10,
	KILL = 11,

	// Buffs
	LOST_TP = 100,
	LOST_LIFE = 101,
	LOST_MP = 102,
	HEAL = 103,
	VITALITY = 104,
	RESURRECT = 105,
	LOSE_STRENGTH = 106,

	// "fun" actions
	SAY = 200,
	LAMA = 201,
	SHOW_CELL = 202,

	// Effects
	ADD_WEAPON_EFFECT = 301,
	ADD_CHIP_EFFECT = 302,
	REMOVE_EFFECT = 303,

	// Other
	ERROR = 1000,
	MAP = 1001,
	AI_ERROR = 1002
};

class Action {
public:
	ActionType type;

	virtual ~Action();

	virtual Json json() const = 0;
};

#endif
