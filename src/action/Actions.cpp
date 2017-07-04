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
		entity->log_length += debug.size();
		if (entity->log_length > MAX_LOGS_ENTITY) {
			return; // Log limit exceeded
		}
		int action_id = actions.size() - 2; // Link the logs to the previous action
		int id = entity->id;
		if (logs[std::to_string(id)].is_null()) {
			logs[std::to_string(id)] = {};
		}
		logs[std::to_string(id)][std::to_string(action_id)].push_back({id, (int) LogType::STANDARD, debug});
		entity->debug_output->str("");
	}
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
