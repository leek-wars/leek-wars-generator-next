#include "FightLoader.hpp"
#include "Fight.hpp"
#include "../util/Util.hpp"
#include "../ai/AI.hpp"
#include "../entity/Team.hpp"
#include "../entity/Leek.hpp"
#include "../entity/Characteristics.hpp"
#include "../field/Field.hpp"
#include "../area/Area.hpp"
#include "FightManager.hpp"

Fight* FightLoader::load(const FightManager& manager, std::string file) {

	auto fight = new Fight();

	// TODO create a Util::read_file_json
	std::string str = Util::read_file(file);
	Json json;
	try {
		json = Json::parse(str);
	} catch (std::exception& e) { // LCOV_EXCL_LINE
		LOG_E << "Invalid fight JSON syntax!" << std::endl;
		return nullptr;
	}

	std::vector<Team*> teams;
	for (const auto& t : json["teams"]) {

		auto team = new Team(teams.size());

		for (const auto& e : t) {

			LOG << "Load entity " << e["name"] << std::endl;

			auto v1 = false;
			if (e.find("v1") != e.end()) {
				v1 = e["v1"];
			}
			auto ai = new AI(Util::read_file(e["ai"]), e["ai"], v1);
			int hat = 0;
			if (e.find("hat") != e.end()) {
				hat = e["hat"];
			}
			int skin = 1;
			if (e.find("skin") != e.end()) {
				skin = e["skin"];
			}
			auto leek = new Leek(fight, e["name"], e["level"], ai, skin, hat);

			Characteristics characs;

			// Primay characteristics
			if (e.find("life") == e.end()) {
				LOG_E << "Missing 'life' attribute!" << std::endl;
				return nullptr;
			}
			characs.set(Characteristic::LIFE, e["life"]);
			if (e.find("tp") == e.end()) {
				LOG_E << "Missing 'life' attribute!" << std::endl;
				return nullptr;
			}
			characs.set(Characteristic::TP, e["tp"]);
			if (e.find("mp") == e.end()) {
				LOG_E << "Missing 'mp' attribute!" << std::endl;
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

			std::vector<Weapon*> weapons;
			if (e.find("weapons") != e.end()) {
				for (const auto& w : e["weapons"]) {
					weapons.push_back(manager.weapons.at(w));
				}
			}
			leek->setWeapons(weapons);

			std::vector<Chip*> chips;
			if (e.find("chips") != e.end()) {
				for (const auto& c : e["chips"]) {
					chips.push_back(manager.chips.at(c));
				}
			}
			leek->setChips(chips);

			leek->team = team;
			leek->farmer = e["farmer"].get<int>();
			team->add_entity(leek);
		}
		teams.push_back(team);
	}

	fight->teams = teams;

	fight->field.reset(new Field(17, 17, 30, teams));

	return fight;
}
