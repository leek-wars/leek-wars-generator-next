#include "AI.hpp"

#include "../module/EntityModule.hpp"

AI::AI(std::string code) {

	this->id = 12765;
	this->name = "SuperIA";
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

	program = new ls::Program(code);
	program->compile(vm, "{}");

	std::cout << "AI : ";
	program->print(std::cout, true);
	std::cout << std::endl;
	this->context = vm.jit_context;
}

void AI::execute(ls::VM& vm) {
	if (program != nullptr) {
		program->execute(vm);
	}
}
