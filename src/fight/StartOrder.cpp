#include <iterator>
#include <algorithm>
#include "StartOrder.hpp"
#include "../entity/Team.hpp"
#include "FightManager.hpp"

StartOrder::StartOrder() {}

StartOrder::~StartOrder() {}

void StartOrder::addEntity(Entity* entity) {

	while (teams.size() < (unsigned) entity->team->id + 1) {
		teams.push_back(std::vector<Entity*>());
	}
	teams[entity->team->id].push_back(entity);
	total_entities++;
}

std::vector<Entity*> StartOrder::compute(FightManager* manager) {

	// Sort entities inside team on their frequency
	for (std::vector<Entity*> team : teams) {
		std::sort(team.begin(), team.end(), [](const Entity* a, const Entity* b) -> bool {
			return a->getFrequency() > b->getFrequency();
		});
	}

	// Compute probability for each team, example : [0.15, 0.35, 0.5]
	std::vector<double> probas;
	std::vector<int> frequencies;

	double sum = 0;
	for (unsigned i = 0; i < teams.size(); ++i) {
		int frequency = teams[i][0]->getFrequency();
		frequencies.push_back(frequency);
		sum += frequency;
	}

	double psum = 0;
	for (unsigned i = 0; i < teams.size(); ++i) {

		double f = frequencies[i];
		double p = 1.0 / (1.0 + pow(10, (sum - f) / 100.0));

		probas.push_back(p);
		psum += p;
	}

	for (unsigned i = 0; i < teams.size(); ++i) {
		probas[i] = probas[i] / psum;
	}
	psum = 1;

	// Compute team order, example : [team3, team1, team2]
	std::vector<int> teamOrder;
	std::vector<int> remaining;
	for (unsigned i = 0; i < teams.size(); ++i) {
		remaining.push_back(i);
	}

	for (unsigned t = 0; t < teams.size(); ++t) {

		double v = (double) manager->random.getDouble() / RAND_MAX;

		for (unsigned i = 0; i < remaining.size(); ++i) {

			int team = remaining[i];
			double p = probas[team];

			if (v <= p) {
				teamOrder.push_back(team);
				remaining.erase(remaining.begin() + i);
				psum -= p;
				break;
			}
			v -= p;
		}
		for (unsigned i = 0; i < teams.size(); ++i) {
			probas[i] = probas[i] / psum;
		}
		psum = 1;
	}

	// Compute entity order : [entity5, entity1, entity2, entity4, ...]
	std::vector<Entity*> order;

	int currentTeamI = 0;
	while (order.size() != total_entities) {

		int team = teamOrder[currentTeamI];
		if (teams[team].size() > 0) {
			Entity* first = teams[team][0];
			order.push_back(first);
			teams[team].erase(teams[team].begin());
		}
		currentTeamI = (currentTeamI + 1) % teams.size();
	}

	return order;
}
