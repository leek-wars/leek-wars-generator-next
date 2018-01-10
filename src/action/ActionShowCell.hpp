#include "Action.hpp"
class Entity;

class ActionShowCell : public Action {
	int leek;
	int cell;
	int color;
public:
	ActionShowCell(Entity* l, int cell, int color);

	Json json() const override;
};
