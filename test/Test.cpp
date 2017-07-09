#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Test.hpp"
#include <leekscript.h>
#include "../benchmark/Benchmark.hpp"
#include "../src/module/LeekModule.hpp"

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

	auto null_value = ls::LSNull::create();
	auto true_value = ls::LSBoolean::create(true);
	auto false_value = ls::LSBoolean::create(false);
	ls::LSNull::set_null_value(null_value);
	ls::LSBoolean::set_true_value(true_value);
	ls::LSBoolean::set_false_value(false_value);

	clock_t begin = clock();
	exeTime = 0;

	test_map();
	test_generateCritical();
	test_fight();
	test_fight_v1();

	///////////////
	LeekModule().generate_doc(std::cout, std::string("doc/Leek_fr.json"));
	// EntityModule().generate_doc(cout, string("doc/Leek_fr.json"));
	Benchmark::pathfinding();
	///////////////

	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Total : " << total << ", succès : " << success << ", erreurs : " << (total - success) << std::endl;
	std::cout << "Total time : " << elapsed_secs * 1000 << " ms, execution time : " << (exeTime / CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
}

void Test::header(std::string text) {
	std::cout << "----------------" << std::endl;
	std::cout << text << std::endl;
	std::cout << "----------------" << std::endl;
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
