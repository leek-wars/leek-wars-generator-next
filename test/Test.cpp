#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Test.hpp"
#include <leekscript/src/leekscript.h>
#include "../benchmark/Benchmark.hpp"
#include "../src/module/LeekModule.hpp"

Test::Test() {
	total = 0;
	success = 0;
	exeTime = 0;
	add_weapons(manager);
	add_chips(manager);
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
	LeekModule().generate_doc(cout, string("doc/Leek_fr.json"));
	// EntityModule().generate_doc(cout, string("doc/Leek_fr.json"));
	Benchmark::pathfinding();
	///////////////

	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Total : " << total << ", succès : " << success << ", erreurs : " << (total - success) << endl;
	cout << "Total time : " << elapsed_secs * 1000 << " ms, execution time : " << (exeTime / CLOCKS_PER_SEC) * 1000 << " ms" << endl;
	cout << "------------------------------------------------" << endl;
}

void Test::header(string text) {
	cout << "----------------" << endl;
	cout << text << endl;
	cout << "----------------" << endl;
}

template <typename T>
void Test::test(std::string message, T expected, T res) {
	total++;
	if (expected != res) {
		cout << "FAUX : " << message << "  =/=>  " << expected << "  got  " << res << endl;
	} else {
		cout << "OK   : " << message << "  ===>  " << res << endl;
		success++;
	}
}

Test::~Test() {}
