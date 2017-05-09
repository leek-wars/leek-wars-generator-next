#include "ActionNewTurn.hpp"

ActionNewTurn::ActionNewTurn(int turn) {
	this->turn = turn;
}

Json ActionNewTurn::json() const {
	return {(int) ActionType::NEW_TURN, turn};
}
