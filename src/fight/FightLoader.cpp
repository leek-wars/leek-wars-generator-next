#include "FightLoader.hpp"
#include "Fight.hpp"
#include "../util/Util.hpp"
#include "../ai/AI.hpp"
#include "../entity/Team.hpp"
#include "../entity/Leek.hpp"
#include "../entity/Characteristics.hpp"
#include "../map/Map.hpp"
#include "../area/Area.hpp"

Fight* FightLoader::load(std::string file) {

	auto fight = new Fight();

	// TODO create a Util::read_file_json
	std::string str = Util::read_file(file);
	Json json;
	try {
		json = Json::parse(str);
	} catch (std::exception& e) { // LCOV_EXCL_LINE
		assert(false); // LCOV_EXCL_LINE
	}

	auto laser = new Weapon(42, "Laser", 6, new Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));
	auto fortress = new Chip(29, "Fortress", 6, 4, false, 0, new Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	std::vector<Team*> teams;
	for (const auto& t : json["teams"]) {

		auto team = new Team();

		for (const auto& e : t["entities"]) {

			auto ai = new AI(Util::read_file(e["ai"]), e["ai"]);
			auto leek = new Leek(fight, e["name"], e["level"], ai);

			Characteristics characs;
			characs.set(Characteristic::LIFE, e["life"]);
			characs.set(Characteristic::TP, e["tp"]);
			characs.set(Characteristic::MP, e["mp"]);
			characs.set(Characteristic::STRENGTH, e["strength"]);
			leek->setCharacteristics(characs);

			vector<Weapon*> weapons;
			weapons.push_back(laser);
			leek->setWeapons(weapons);

			vector<Chip*> chips;
			chips.push_back(fortress);
			leek->setChips(chips);

			leek->team = teams.size();
			team->add_entity(leek);
		}
		teams.push_back(team);
	}

	fight->teams = teams;

	fight->map.reset(new Map(18, 18, 30, teams));

	return fight;
}
