#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Test.hpp"
#include <leekscript.h>

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

template <typename T>
void Test::test(std::string message, T expected, T res) {
	total++;
	if (expected != res) {
		std::cout << "FAUX : " << message << "  =/=>  " << expected << "  got  " << res << std::endl;
	} else {
		std::cout << "OK   : " << message << "  ===>  " << res << std::endl;
		success++;
	}
}

Test::~Test() {}
