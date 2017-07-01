#include "FightManager.hpp"
#include "../module/FightModule.hpp"
#include "../module/EntityModule.hpp"
#include "../module/MapModule.hpp"
#include "../module/CellModule.hpp"
#include "../module/LeekModule.hpp"
#include "../module/WeaponModule.hpp"
#include "../module/ColorModule.hpp"
#include "../module/ChipModule.hpp"
#include "../util/Util.hpp"
#include "../entity/Entity.hpp"

FightManager* FightManager::current;

FightManager::FightManager() : vm(), vm_v1(true) {
	// V2
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());

	// V1
	auto entity_module = new EntityModule();
	vm_v1.add_module(new FightModule());
	vm_v1.add_module(entity_module);
	vm_v1.add_module(new LeekModule());
	vm_v1.add_module(new MapModule());
	vm_v1.add_module(new CellModule());
	vm_v1.add_module(new WeaponModule());
	vm_v1.add_module(new ColorModule());
	vm_v1.add_module(new ChipModule());

	for (auto& method : entity_module->static_methods) {
		if (method.name.at(0) == '_') {
			auto fun = new ls::LSFunction<ls::LSValue*>(method.impl[0].addr);
			fun->refs = 1;
			fun->native = true;
			vm_v1.add_constant(method.name.substr(1), method.impl[0].type, fun);
		}
	}
}

std::string FightManager::compile(std::string ai) {

	LOG << "Compile AI " << ai << std::endl;

	auto code = Util::read_file(ai);
	auto name = ai;

	ls::VM::current_vm = &vm;
	auto program = new ls::Program(code, name);
	auto result = program->compile(vm, "{}");

	auto errors = Json::array();
	for (const auto& e : result.lexical_errors) {
		errors.push_back(e.json());
	}
	for (const auto& e : result.syntaxical_errors) {
		errors.push_back(e.json());
	}
	for (const auto& e : result.semantical_errors) {
		errors.push_back(e.json());
	}
	return errors.dump();
}

void FightManager::start(Fight& fight, std::function<void(Report*)> callback) {

	this->start_time = chrono::high_resolution_clock::now();
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
	LOG_W << "Fight crashed while '" << current_player->name << "' was playing" << std::endl;

	end(fight->crash());
}

void FightManager::end(Report* report) {

	auto end_time = chrono::high_resolution_clock::now();
	long time_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - this->start_time).count();
	double time_ms = (((double) time_ns / 1000) / 1000);
	LOG << "-------------- end of fight ----------------" << std::endl;
	LOG << "time: " << time_ms << " ms" << endl;

	callback(report);
}
