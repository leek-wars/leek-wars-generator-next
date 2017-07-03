#include <algorithm>
#include <string>

#include "Attack.hpp"
#include "Effect.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Summon.hpp"
#include "../area/Area.hpp"
#include "../util/Util.hpp"
#include "../area/AreaSingleCell.hpp"
#include "../area/AreaCircle.hpp"
#include "../area/AreaLaserLine.hpp"

using namespace std;

Attack::Attack(int min_range, int max_range, LaunchType launch_type, AreaType area_type, bool los, std::vector<EffectParameters> effects, AttackType attack_type) {

	this->min_range = min_range;
	this->max_range = max_range;
	this->launch_type = launch_type;
	this->area.reset(Attack::getArea(this, area_type));
	this->need_los = los;
	this->attack_type = attack_type;

	for (const auto& e : effects) {
		if (e.type == EffectType::HEAL) {
			healAttack |= e.targets;
		}
		if (e.type == EffectType::DAMAGE) {
			dammageAttack |= e.targets;
		}
	}
}

Attack::~Attack() {}

const EffectParameters* Attack::getEffectParametersByType(const EffectType type) const {
	for (const EffectParameters& ep : effects) {
		if (ep.id == type) {
			return &ep;
		}
	}
	return nullptr;
}

std::vector<Entity*> Attack::applyOnCell(Fight* fight, Entity* caster, Cell* target, int item_id, bool critical) const {

	std::vector<Entity*> return_entities;

	if (effects.size() > 0 && effects[0].id == EffectType::TELEPORT) {

		caster->has_moved = true;
		Cell* start = caster->cell;
		caster->setCell(nullptr);

		start->setEntity(nullptr);
		target->setEntity(caster);

		return { caster };
	}

	// On suppose que l'autorisation de lancer le sort (minRange, maxRange,
	// launchType) a été vérifiée avant l'appel

	// On récupère les cases cibles
	std::vector<Cell*> target_cells = area->getArea(caster->cell, target);

	// On trouve les poireaux sur ces cellules
	std::vector<Entity*> target_entities;

	for (Cell* cell : target_cells) {
		// cout << "entity on cell " << cell->id << " : " << cell->entity << endl;
		if (cell->entity != nullptr) {
			target_entities.push_back(cell->entity);
		}
	}

	// On défini le jet
	double jet = Util::random();

	// Apply effects
	for (EffectParameters parameters : effects) {

		for (Entity* targetEntity : target_entities) {

			if (targetEntity->isDead()) {
				continue;
			}
			if (!filterTarget(parameters.targets, caster, targetEntity)) {
				continue;
			}

			if (std::find(return_entities.begin(), return_entities.end(), targetEntity) == return_entities.end()) {
				return_entities.push_back(targetEntity);
			}
			double power = getPowerForCell(caster->cell, target, targetEntity->cell);

			Effect::createEffect(fight, parameters.id, parameters.turns, power, parameters.value1, parameters.value2, critical, targetEntity, caster, attack_type, item_id, jet);
		}
	}
	return return_entities;
}

bool Attack::filterTarget(int targets, Entity* caster, Entity* target) const {

	// Enemies
	if ((targets & EffectTarget::ENEMIES) == 0 && caster->team != target->team) {
		return false;
	}

	// Allies
	if ((targets & EffectTarget::ALLIES) == 0 && caster->team == target->team) {
		return false;
	}

	// Caster
	if ((targets & EffectTarget::CASTER) == 0 && caster == target) {
		return false;
	}

	bool summon = (dynamic_cast<Summon*>(target) != nullptr);

	// Non-Summons
	if ((targets & EffectTarget::NON_SUMMONS) == 0 && !summon) {
		return false;
	}

	// Summons
	if ((targets & EffectTarget::SUMMONS) == 0 && summon) {
		return false;
	}

	return true;
}

// Compute the area effect attenuation : 100% at center, 50% on the border
double Attack::getPowerForCell(Cell*, Cell* target_cell, Cell* curent_cell) const {

	if (area->getRadius() == 0) {
		return 1.0;
	}
	int dist = target_cell->map->getCellDistance(target_cell, curent_cell);
	return (area->getRadius() - dist) / area->getRadius() * 0.5 + 0.5;
}

Area* Attack::getArea(Attack* attack, AreaType type) {
	if (type == AreaType::SINGLE_CELL)
		return new AreaSingleCell(attack);
	else if (type == AreaType::LASER_LINE)
		return new AreaLaserLine(attack);
	else if (type == AreaType::CIRCLE1)
		return new AreaCircle(attack, 1);
	else if (type == AreaType::CIRCLE2)
		return new AreaCircle(attack, 2);
	else if (type == AreaType::CIRCLE3)
		return new AreaCircle(attack, 3);
	return nullptr;
}
