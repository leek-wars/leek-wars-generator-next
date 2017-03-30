#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Test.hpp"
#include <leekscript/src/leekscript.h>

using namespace std;

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

	clock_t begin = clock();
	exeTime = 0;

	/*
	 * General
	 */
	header("General");

	test("ai.ls", 12, 12);


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
