#include "FightManager.hpp"
#include "../module/FightModule.hpp"
#include "../module/EntityModule.hpp"
#include "../module/FieldModule.hpp"
#include "../module/CellModule.hpp"
#include "../module/LeekModule.hpp"
#include "../module/WeaponModule.hpp"
#include "../module/ColorModule.hpp"
#include "../module/ChipModule.hpp"
#include "../util/Util.hpp"
#include "../entity/Entity.hpp"

FightManager* FightManager::current;

FightManager::FightManager() : vm(), vm_v1(true) {

	// Load items
	auto build_attack = [](Json i, AttackType type) {
		std::vector<EffectParameters> effects;
		for (const auto& e : i["effects"]) {
			auto id = (EffectType) e["id"].get<int>();
			effects.push_back({id, e["value1"], e["value2"], e["turns"], e["targets"], Effect::isStackable(id)});
		}
		return new Attack(i["min_range"], i["max_range"], (LaunchType) i["launch_type"].get<int>(), (AreaType) i["area"].get<int>(), i["los"].get<int>(), effects, type);
	};

	// Load weapons
	auto weapons_json = Json::parse(Util::read_file("data/weapons.json"));
	for (const auto& w : weapons_json) {
		auto weapon = new Weapon(w["id"], w["name"], w["cost"], build_attack(w, AttackType::WEAPON), w["template"]);
		weapons.insert({w["id"].get<int>(), weapon});
	}

	// Load chips
	auto chips_json = Json::parse(Util::read_file("data/chips.json"));
	for (const auto& c : chips_json) {
		auto chip = new Chip(c["id"], c["name"], c["cost"], c["cooldown"], c["team_cooldown"].get<int>(), c["initial_cooldown"], build_attack(c, AttackType::CHIP), c["template"]);
		chips.insert({c["id"].get<int>(), chip});
	}

	// V2
	vm.add_module(new FightModule(&vm));
	vm.add_module(new EntityModule(&vm));
	vm.add_module(new LeekModule(&vm));
	vm.add_module(new FieldModule(&vm));
	vm.add_module(new CellModule(&vm));
	vm.add_module(new ItemModule(&vm));
	vm.add_module(new WeaponModule(&vm, *this));
	vm.add_module(new ColorModule(&vm));
	vm.add_module(new ChipModule(&vm, *this));

	// V1
	auto entity_module = new EntityModule(&vm);
	vm_v1.add_module(new FightModule(&vm));
	vm_v1.add_module(entity_module);
	vm_v1.add_module(new LeekModule(&vm));
	vm_v1.add_module(new FieldModule(&vm));
	vm_v1.add_module(new CellModule(&vm));
	vm_v1.add_module(new ItemModule(&vm));
	vm_v1.add_module(new WeaponModule(&vm, *this));
	vm_v1.add_module(new ColorModule(&vm));
	vm_v1.add_module(new ChipModule(&vm, *this));

	// Load forbidden words
	censor.load("data/forbidden_words.txt");
}

std::string FightManager::compile(std::string ai) {

	LOG << "Compile AI " << ai << std::endl;

	auto code = Util::read_file(ai);
	auto name = ai;

	ls::VM::current_vm = &vm;
	auto program = new ls::Program(code, name);
	auto result = program->compile(vm);

	LOG << "AI: " << program << std::endl;

	auto errors = Json::array();
	for (const auto& e : result.errors) {
		LOG << e.message() << std::endl;
		errors.push_back(e.json());
	}
	return errors.dump();
}

void FightManager::start(Fight& fight, std::function<void(Report*)> callback) {

	this->start_time = std::chrono::high_resolution_clock::now();
	this->fight = &fight;
	this->callback = callback;
	FightManager::current = this;

	// Register a segfault catcher
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = [](int signal, siginfo_t* si, void* arg) {
		LOG_E << "Caught signal " << signal << " at address " << si->si_addr << ", arg: " << arg << std::endl;
		FightManager::current->crash();
	};
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	end(fight.start(vm, vm_v1));
}

void FightManager::crash() {

	auto current_player = fight->order.current();
	LOG_W << "Fight crashed while '" << current_player->name << "' was playing with AI '" << current_player->ai->name << "'" << std::endl;

	end(fight->crash());
}

void FightManager::end(Report* report) {

	auto end_time = std::chrono::high_resolution_clock::now();
	long time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - this->start_time).count();
	double time_ms = (((double) time_ns / 1000) / 1000);
	LOG << "-------------- end of fight ----------------" << std::endl;
	LOG << "time: " << time_ms << " ms" << std::endl;

	callback(report);
}
