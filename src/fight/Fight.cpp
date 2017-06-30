#include <chrono>
#include <vector>
#include "Fight.hpp"

#include "Simulator.hpp"
#include "../map/Map.hpp"
#include "../effect/Effect.hpp"
#include "../item/Chip.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../util/Util.hpp"
#include "../effect/Attack.hpp"
#include "../action/ActionStartFight.hpp"
#include "../action/ActionUseChip.hpp"
#include "../action/ActionUseWeapon.hpp"
#include "../action/ActionLoseMP.hpp"
#include "../action/ActionMove.hpp"
#include "../action/ActionNewTurn.hpp"

using namespace std;

Fight::Fight() {
	map = nullptr;
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
		try {
			LOG << "Turn of " << entity->name << " (" << entity->id << "), AI " << entity->ai->name << "..." << std::endl;
			entity->ai->execute(vm, vm_v1);
		} catch (ls::vm::ExceptionObj* ex) {
			std::cout << ex->to_string(true);
			// delete ex;
			vm.last_exception = nullptr;
			vm_v1.last_exception = nullptr;
		}
		entity->endTurn();
		if (order.next()) {
			actions.add(new ActionNewTurn(order.getTurn()));
			LOG << "Turn " << order.getTurn() << std::endl;
		}
	}

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
	} catch (exception& e) {
		return nullptr;
	}
}

int Fight::moveEntity(Entity* entity, const vector<const Cell*> path) {

	int size = path.size();
	if (size == 0) {
		return 0;
	}
	if (size > entity->getMP()) {
		return 0;
	}
	actions.add(new ActionMove(entity, path));
	actions.add(new ActionLoseMP(entity, size));

	// TODO Statistics
//	trophyManager.deplacement(entity.getFarmer(), path);

	entity->useMP(size);
	entity->has_moved = true;
	entity->cell->setEntity(nullptr);
	entity->setCell((Cell*) path[path.size() - 1]);
	entity->cell->setEntity(entity);

	return path.size();
}

bool Fight::hasCooldown(const Entity* entity, const Chip* chip) const {
	if (chip == nullptr) {
		return false;
	}
	if (chip->team_cooldown) {
		return teams[entity->team]->hasCooldown(chip->id);
	} else {
		return entity->hasCooldown(chip->id);
	}
}

bool Fight::generateCritical(Entity* entity) const {
	return Util::random() < ((double) entity->getAgility() / 1000);
}

int Fight::useWeapon(Entity* launcher, Cell* target) {

	if (order.current() != launcher || launcher->weapon == nullptr) {
		return AttackResult::INVALID_TARGET;
	}

	const Weapon* weapon = launcher->weapon;

//	cout << "weapon cost : " << weapon->cost << endl;
//	cout << "entity tp : " << launcher->getTP() << endl;

	if (weapon->cost > launcher->getTP()) {
		return AttackResult::NOT_ENOUGH_TP;
	}

	if (!map->canUseAttack(launcher->cell, target, weapon->attack.get())) {
		return AttackResult::INVALID_POSITION;
	}

	bool critical = generateCritical(launcher);
	AttackResult result = critical ? AttackResult::CRITICAL : AttackResult::SUCCESS;

	ActionUseWeapon* action = new ActionUseWeapon(launcher, target, weapon, result);
	actions.add(action);

	vector<Entity*> target_entities  = weapon->attack.get()->applyOnCell(this, launcher, target, weapon->id, critical);

	// TODO
	//trophyManager.weaponUsed(launcher, weapon, target_entities);

	action->set_entities(target_entities);

	launcher->useTP(weapon->cost);

	// TODO
	//actions.log(new ActionLoseTP(launcher, weapon.getWeaponTemplate().getCost()));

	return result;
}

int Fight::useChip(Entity* caster, Cell* target, Chip* chip) {

	cout << "useChip() start" << endl;

	cout << "id : " << caster->id << endl;
	cout << "cost : " << chip->cost << endl;
	cout << "tp : " << caster->getTP() << endl;

	if (order.current() != caster) {
		return AttackResult::INVALID_TARGET;
	}

	cout << "useChip() good order" << endl;

	if (chip->cost > caster->getTP()) {
		return AttackResult::NOT_ENOUGH_TP;
	}
	cout << "useChip() good cost" << endl;

	if (!map->canUseAttack(caster->cell, target, chip->attack.get())) {
		return AttackResult::INVALID_POSITION;
	}

	cout << "useChip() map config ok" << endl;

	if (hasCooldown(caster, chip)) {
		return AttackResult::INVALID_COOLDOWN;
	}

	cout << "useChip() valid" << endl;

	// Summon (with no AI)
	if (chip->attack.get()->getEffectParametersByType(EffectType::SUMMON) != nullptr) {
		// TODO
		//return summonEntity(caster, target, chip, nullptr);
	}

	// Si c'est une téléportation on ajoute une petite vérification
	if (chip->id == ChipID::TELEPORTATION) {
		if (!target->available()) {
			return AttackResult::INVALID_TARGET;
		}
	}

	bool critical = generateCritical(caster);
	int result = critical ? AttackResult::CRITICAL : AttackResult::SUCCESS;

	ActionUseChip* action = new ActionUseChip(caster, target, chip, result);
	actions.add(action);

	vector<Entity*> target_leeks = chip->attack.get()->applyOnCell(this, caster, target, chip->id, critical);

	action->set_entities(target_leeks);

	// TODO
	// trophyManager.spellUsed(caster, chip, target_leeks);

	if (chip->cooldown != 0) {
		// addCooldown(caster, chip);
	}

	caster->useTP(chip->cost);
	//logs.log(new ActionLoseTP(caster, chip->getCost()));

	return result;
}

Json Fight::entities_json() const {
	Json json;
	for (const auto& e : entities) {
		json.push_back(e.second->to_json());
	}
	return json;
}
