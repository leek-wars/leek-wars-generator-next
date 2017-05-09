#ifndef ACTION_NEW_TURN_HPP
#define ACTION_NEW_TURN_HPP

#include "Action.hpp"

class ActionNewTurn : public Action {
	int turn;
public:

	ActionNewTurn(int turn);

	virtual Json json() const override;
};

#endif
