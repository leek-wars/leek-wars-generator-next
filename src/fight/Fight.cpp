#include <chrono>
#include <vector>
#include "Fight.hpp"
#include "Simulator.hpp"
#include "../field/Field.hpp"
#include "../effect/Effect.hpp"
#include "../item/Chip.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../util/Util.hpp"
#include "../effect/Attack.hpp"
#include "../action/ActionStartFight.hpp"
#include "../action/ActionUseChip.hpp"
#include "../action/ActionUseWeapon.hpp"
#include "../action/ActionNewTurn.hpp"
#include "../action/ActionEndTurn.hpp"
#include "../action/ActionEntityTurn.hpp"
#include "../action/ActionAIError.hpp"

Fight::Fight() : actions(this) {
	field = nullptr;
	turn = 0;
	Entity::next_id = 0;
}

Fight::~Fight() {
	for (auto& team : teams) {
		delete team;
	}
}

Report* Fight::start(ls::VM& vm, ls::VM& vm_v1) {

	Simulator::fight = this;

	for (auto& team : teams) {
		for (auto& entity : team->entities) {
			entities.insert({entity->id, entity});
			order.addEntity(entity);
			entity->ai->compile(vm, vm_v1);
		}
	}

	actions.add(new ActionStartFight());

	while (order.getTurn() <= MAX_TURNS) {

		auto entity = order.current();
		Simulator::entity = entity;
		vm.output = entity->debug_output;
		vm_v1.output = entity->debug_output;

		LOG << "Turn of " << entity->name << " (" << entity->id << "), AI " << entity->ai->name << "..." << std::endl;
		actions.add(new ActionEntityTurn(entity));
		try {
			entity->ai->execute(vm, vm_v1);
		} catch (ls::vm::ExceptionObj* ex) {
			LOG << ex->to_string(true);
			vm.last_exception = nullptr;
			vm_v1.last_exception = nullptr;
			if (ex->type == ls::vm::Exception::OPERATION_LIMIT_EXCEEDED) {
				actions.add(new ActionAIError(entity));
				// TODO Add Breaker Trophy
			}
			// TODO delete ex
		}
		vm.operations = 0;
		entity->endTurn();
		actions.add(new ActionEndTurn(entity));
		if (order.next()) {
			actions.add(new ActionNewTurn(order.getTurn()));
			LOG << "Turn " << order.getTurn() << std::endl;
		}
	}

	Simulator::entity = nullptr;

	Report* report = new Report(this);
	report->actions = &actions;
	return report;
}

Report* Fight::crash() {

	Report* report = new Report(this);
	report->actions = &actions;
	return report;
}

Entity* Fight::getEntity(int id) {
	try {
		return entities.at(id);
	} catch (std::exception& e) {
		return nullptr;
	}
}

bool Fight::hasCooldown(const Entity* entity, const Chip* chip) const {
	if (chip == nullptr) {
		return false;
	}
	if (chip->team_cooldown) {
		return entity->team->hasCooldown(chip->id);
	} else {
		return entity->hasCooldown(chip->id);
	}
}

bool Fight::generateCritical(Entity* entity) const {
	return Util::random() < ((double) entity->getAgility() / 1000);
}

int Fight::useWeapon(Entity* launcher, Cell* target) {

	if (order.current() != launcher || launcher->weapon == nullptr) {
		LOG << launcher->name << " tries to shoot without a weapon" << std::endl;
		return AttackResult::INVALID_TARGET;
	}
	auto weapon = launcher->weapon;

	LOG << launcher->name << " (" << launcher->id << ") uses weapon " << weapon->name << " (" << weapon->id << ") : costs " << weapon->cost << ", tp: " << launcher->getTP() << std::endl;

	if (weapon->cost > launcher->getTP()) {
		return AttackResult::NOT_ENOUGH_TP;
	}
	if (!field->can_use_attack(launcher->cell, target, weapon->attack.get())) {
		return AttackResult::INVALID_POSITION;
	}

	bool critical = generateCritical(launcher);
	AttackResult result = critical ? AttackResult::CRITICAL : AttackResult::SUCCESS;

	auto action = new ActionUseWeapon(launcher, target, weapon, result);
	actions.add(action);

	auto target_entities  = weapon->attack.get()->applyOnCell(this, launcher, target, weapon->id, critical);

	// TODO Trophy manager
	// trophyManager.weaponUsed(launcher, weapon, target_entities);

	action->set_entities(target_entities);

	launcher->useTP(weapon->cost);

	return result;
}

int Fight::useChip(Entity* caster, Cell* target, Chip* chip) {

	LOG << caster->name << " (" << caster->id << ") uses chip " << chip->name << " (" << chip->id << ") : costs " << chip->cost << ", tp: " << caster->getTP() << std::endl;

	if (order.current() != caster) {
		return AttackResult::INVALID_TARGET;
	}
	if (chip->cost > caster->getTP()) {
		return AttackResult::NOT_ENOUGH_TP;
	}
	if (!field->can_use_attack(caster->cell, target, chip->attack.get())) {
		return AttackResult::INVALID_POSITION;
	}
	if (hasCooldown(caster, chip)) {
		return AttackResult::INVALID_COOLDOWN;
	}
	// Summon (with no AI)
	if (chip->attack.get()->getEffectParametersByType(EffectType::SUMMON) != nullptr) {
		// TODO Summon management
		//return summonEntity(caster, target, chip, nullptr);
	}
	// Check destination cell in case of a teleportation
	if (chip->attack->effects.size() && chip->attack->effects.at(0).type == EffectType::TELEPORT) {
		if (!target->available()) {
			return AttackResult::INVALID_TARGET;
		}
	}

	bool critical = generateCritical(caster);
	int result = critical ? AttackResult::CRITICAL : AttackResult::SUCCESS;

	auto action = new ActionUseChip(caster, target, chip, result);
	actions.add(action);

	auto target_leeks = chip->attack.get()->applyOnCell(this, caster, target, chip->id, critical);

	action->set_entities(target_leeks);

	// TODO Trophy manager
	// trophyManager.spellUsed(caster, chip, target_leeks);

	if (chip->cooldown != 0) {
		// TODO addCooldown
		// addCooldown(caster, chip);
	}

	caster->useTP(chip->cost);

	return result;
}

Json Fight::entities_json() const {
	Json json;
	for (const auto& e : entities) {
		json.push_back(e.second->to_json());
	}
	return json;
}
