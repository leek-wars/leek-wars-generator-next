#include "ActionLama.hpp"
#include "../entity/Entity.hpp"

ActionLama::ActionLama(Entity* caster) : caster(caster->id) {}

Json ActionLama::json() const {
	return {(int) ActionType::LAMA, caster};
}
