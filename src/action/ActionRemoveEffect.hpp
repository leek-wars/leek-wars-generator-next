#ifndef ACTION_REMOVE_EFFECT_HPP
#define ACTION_REMOVE_EFFECT_HPP

#include "Action.hpp"

class ActionRemoveEffect : public Action {
	int id;
public:
	ActionRemoveEffect(int id);

	virtual Json json() const override;
};

#endif
