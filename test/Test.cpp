#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Test.hpp"
#include <leekscript.h>
#include "../src/fight/Simulator.hpp"

Test::Test() {
	total = 0;
	success = 0;
	exeTime = 0;
}

int main(int, char**) {

	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter();
	llvm::InitializeNativeTargetAsmParser();

	srand(time(0));
	Util::log_enabled = false;
	Test().tests();
	return 0;
}

void Test::tests() {

	clock_t begin = clock();
	exeTime = 0;

	// Run tests
	test_types();
	test_field();
	test_generateCritical();
	test_censor();
	test_fight();
	test_fight_v1();
	test_doc();

	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Total : " << total << ", succès : " << success << ", erreurs : " << (total - success) << std::endl;
	std::cout << "Total time : " << elapsed_secs * 1000 << " ms, execution time : " << (exeTime / CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;
	if ((total - success) == 0) {
		std::cout << GREEN << "GOOD! ✔" << END_COLOR << std::endl;
	} else {
		std::cout << RED << "BAD! : " << (total - success) << " error(s) ✘" << END_COLOR << std::endl;
	}
	std::cout << "------------------------------------------------" << std::endl;
}

void Test::header(std::string text) {
	std::cout << "╔";
	for (unsigned i = 0; i < text.size() + 2; ++i) std::cout << "═";
	std::cout << "╗" << std::endl;
	std::cout << "║ " << text << " ║" << std::endl;
	std::cout << "╚";
	for (unsigned i = 0; i < text.size() + 2; ++i) std::cout << "═";
	std::cout << "╝";
	std::cout << std::endl;
}

void Test::test_ai(Fight* fight, Entity* entity, std::string code, std::string expected) {
	auto ai = new AI(code, "ai", false);
	entity->ai.reset(ai);
	int errors = entity->ai->compile(manager.vm, manager.vm_v1);
	// entity->ai->program->print(std::cout, true);
	// std::cout << std::endl;
	if (errors > 0) {
		std::cout << errors << " error(s) in AI!" << std::endl;
	}
	Simulator::fight = fight;
	Simulator::entity = entity;
	manager.vm.output = entity->debug_output;
	manager.vm_v1.output = entity->debug_output;
	fight->manager = &manager;
	std::string actual;
	try {
		actual = entity->ai->execute(manager.vm, manager.vm_v1);
	} catch (ls::vm::ExceptionObj* ex) {
		std::cout << "Exception thrown! " << ls::vm::ExceptionObj::exception_message(ex->type) << std::endl;
		// manager.vm.last_exception = nullptr;
		// manager.vm_v1.last_exception = nullptr;
	}
	test(code, expected, actual);
}

Test::~Test() {}
