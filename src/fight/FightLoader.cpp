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

	auto pistol = new Weapon(37, "Pistol", 3, new Attack(1, 7, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "1,15,5,0,31", AttackType::WEAPON));
	auto laser = new Weapon(42, "Laser", 6, new Attack(2, 7, LaunchType::LINE, AreaType::LASER_LINE, true, "1,43,16,0,31", AttackType::WEAPON));
	auto fortress = new Chip(29, "Fortress", 6, 4, false, 0, new Attack(0, 6, LaunchType::CIRCLE, AreaType::SINGLE_CELL, true, "5,10,5,3,31", AttackType::CHIP));

	std::vector<Team*> teams;
	for (const auto& t : json["teams"]) {

		auto team = new Team();

		for (const auto& e : t["entities"]) {

			LOG << "Load entity " << e["name"] << std::endl;

			auto ai = new AI(Util::read_file(e["ai"]), e["ai"]);
			auto leek = new Leek(fight, e["name"], e["level"], ai);

			Characteristics characs;

			// Primay characteristics
			if (e.find("life") == e.end()) {
				LOGW << "Missing 'life' attribute!" << std::endl;
				return nullptr;
			}
			characs.set(Characteristic::LIFE, e["life"]);
			if (e.find("tp") == e.end()) {
				LOGW << "Missing 'life' attribute!" << std::endl;
				return nullptr;
			}
			characs.set(Characteristic::TP, e["tp"]);
			if (e.find("mp") == e.end()) {
				LOGW << "Missing 'mp' attribute!" << std::endl;
				return nullptr;
			}
			characs.set(Characteristic::MP, e["mp"]);

			// Secondary characteristics (not mandatory)
			if (e.find("strength") != e.end()) {
				characs.set(Characteristic::STRENGTH, e["strength"]);
			}
			if (e.find("agility") != e.end()) {
				characs.set(Characteristic::AGILITY, e["agility"]);
			}
			if (e.find("science") != e.end()) {
				characs.set(Characteristic::SCIENCE, e["science"]);
			}
			if (e.find("magic") != e.end()) {
				characs.set(Characteristic::MAGIC, e["magic"]);
			}
			if (e.find("resistance") != e.end()) {
				characs.set(Characteristic::RESISTANCE, e["resistance"]);
			}
			if (e.find("frequency") != e.end()) {
				characs.set(Characteristic::FREQUENCY, e["frequency"]);
			}
			leek->setCharacteristics(characs);

			vector<Weapon*> weapons;
			weapons.push_back(pistol);
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
