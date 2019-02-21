#include "Actions.hpp"
#include "Action.hpp"
#include "../fight/Simulator.hpp"
#include "../entity/Entity.hpp"
#include "../util/Util.hpp"

#define MAX_LOGS_ENTITY 50000

Actions::Actions(Fight* fight) : fight(fight) {}

Actions::~Actions() {
	for (auto& a : actions) {
		delete a;
	}
}

int Actions::getEffectId() {
	return effect_id++;
}

void Actions::add(Action* action) {
	actions.push_back(action);

	// Add personal logs
	if (Simulator::entity) {
		add_entity_logs(Simulator::entity);
	}
}

void Actions::add_entity_logs(Entity* entity) {
	auto debug = entity->debug_output->str();
	if (debug.size()) {
		if (debug.back() == '\n') debug.pop_back();
		add_log(entity, {entity->id, (int) LogType::STANDARD, debug}, debug.size());
		entity->debug_output->str("");
	}
}

bool Actions::add_mark(Entity* entity, std::vector<const Cell*> cells, int color, int duration) {
	std::vector<int> cells_int;
	for (const auto& cell : cells) {
		cells_int.push_back(cell->id);
	}
	return add_log(entity, {entity->id, (int) LogType::MARK, cells_int, Util::int_to_hex_color(color), duration}, cells.size() * 5 + 8);
}

bool Actions::add_log(Entity* entity, Json&& json, int cost) {
	entity->log_length += cost;
	if (entity->log_length > MAX_LOGS_ENTITY) {
		return false; // Log limit exceeded
	}
	int action_id = actions.size() - 1; // Link the logs to the previous action
	auto id = std::to_string(entity->farmer);
	if (logs[id].is_null()) {
		logs[id] = {};
	}
	logs[id][std::to_string(action_id)].push_back(json);
	return true;
}

int Actions::getNextId() {
	return actions.size();
}

Json Actions::json() {
	Json actions_json { };
	for (auto action : actions) {
		actions_json.push_back(action->json());
	}
	return actions_json;
}
