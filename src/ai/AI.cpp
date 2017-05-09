#include "AI.hpp"

#include "../module/EntityModule.hpp"

AI::AI(std::string code, std::string ai_name, bool v1) {
	this->id = 12765;
	this->name = ai_name;
	this->code = code;
	this->program = nullptr;
	this->v1 = v1;
}

AI::~AI() {
	if (program != nullptr) {
		delete program;
	}
}

void AI::compile(ls::VM& vm, ls::VM& vm_v1) {
	
	ls::VM::current_vm = v1 ? &vm_v1 : &vm;
	program = new ls::Program(code, name);
	program->compile(v1 ? vm_v1 : vm, "{}");

	std::cout << "AI [" << name << "] : ";
	program->print(std::cout, true);
	std::cout << std::endl;
}

void AI::execute(ls::VM& vm, ls::VM& vm_v1) {
	if (program != nullptr) {
		ls::VM::current_vm = v1 ? &vm_v1 : &vm;
		program->execute(*ls::VM::current_vm);
	}
}
