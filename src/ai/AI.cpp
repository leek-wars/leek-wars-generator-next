#include "AI.hpp"

#include "../module/EntityModule.hpp"

AI::AI(std::string code, std::string ai_name) {

	this->id = 12765;
	this->name = ai_name;
	this->code = code;
	this->program = nullptr;
}

AI::~AI() {
	if (program != nullptr) {
		delete program;
	}
	jit_context_destroy(context);
}

void AI::compile(ls::VM& vm) {

	program = new ls::Program(code, name);
	program->compile(vm, "{}");

	std::cout << "AI [" << name << "] : ";
	program->print(std::cout, true);
	std::cout << std::endl;
	this->context = vm.jit_context;
}

void AI::execute(ls::VM& vm) {
	if (program != nullptr) {
		program->execute(vm);
	}
}
