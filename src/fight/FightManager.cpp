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

Report* FightManager::start(Fight& fight) {

	this->fight = &fight;

	return fight.start(vm, vm_v1);
}

Report* FightManager::crash() {

	auto current_player = fight->order.current();
	LOG << "Fight crashed while this entity was playing: " << current_player->name << std::endl;

	Report* report = new Report(fight);
	report->actions = new Actions();
	return report;
}
