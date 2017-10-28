#include "ActionRemoveEffect.hpp"

ActionRemoveEffect::ActionRemoveEffect(int id) {
	this->id = id;
}

Json ActionRemoveEffect::json() const {
	return {(int) ActionType::REMOVE_EFFECT, id};
}
