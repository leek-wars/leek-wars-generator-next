#include "ActionShowCell.hpp"
#include "../util/Util.hpp"
#include "../entity/Entity.hpp"

ActionShowCell::ActionShowCell(Entity* e, int cell, int color) {
	this->leek = e->id;
	this->cell = cell;
	this->color = color;
}

Json ActionShowCell::json() const {
	return {(int) ActionType::SHOW_CELL, leek, cell, Util::int_to_hex_color(color)};
}
