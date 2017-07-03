#include "ActionMove.hpp"

ActionMove::ActionMove(Entity* entity, vector<const Cell*> path) {
	this->entity = entity->id;
	for (auto cell : path) {
		this->path.push_back(cell->id);
	}
	end = path[path.size() - 1]->id;
}

Json ActionMove::json() const {
	return {(int) ActionType::MOVE_TO, entity, end, path};
}
