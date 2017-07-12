#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Test.hpp"
#include <leekscript.h>
#include "../src/fight/Simulator.hpp"
#include "../src/colors.h"

Test::Test() {
	total = 0;
	success = 0;
	exeTime = 0;
}

int main(int, char**) {
	srand(time(0));
	Test().tests();
	return 0;
}

void Test::tests() {

	// Global initialization
	ls::LSNull::set_null_value(ls::LSNull::create());
	ls::LSBoolean::set_true_value(ls::LSBoolean::create(true));
	ls::LSBoolean::set_false_value(ls::LSBoolean::create(false));

	clock_t begin = clock();
	exeTime = 0;

	// Run tests
	test_field();
	test_pathfinding();
	test_line_of_sight();
	test_generateCritical();
	test_fight();
	test_fight_v1();
	test_doc();

	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Total : " << total << ", succès : " << success << ", erreurs : " << (total - success) << std::endl;
	std::cout << "Total time : " << elapsed_secs * 1000 << " ms, execution time : " << (exeTime / CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;
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
	entity->ai->compile(manager.vm, manager.vm_v1);
	Simulator::entity = entity;
	manager.vm.output = entity->debug_output;
	manager.vm_v1.output = entity->debug_output;
	auto actual = entity->ai->execute(manager.vm, manager.vm_v1);
	test(code, expected, actual);
}

template <typename T>
void Test::test(std::string code, T expected, T res) {
	total++;
	if (expected != res) {
		std::cout << RED << "FAUX" << END_COLOR << " : " << code << "  =/=>  " << expected << "  got  " << res << std::endl;
	} else {
		std::cout << GREEN << "OK" << END_COLOR << "   : " << code << "  ===>  " << res << std::endl;
		success++;
	}
}

Test::~Test() {}
