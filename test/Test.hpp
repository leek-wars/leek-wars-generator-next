#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <string>

class Test {

	int total;
	int success;
	double exeTime;

public:

	Test();
	virtual ~Test();


	std::string run_fight();

	void tests();
	void header(std::string);

	template <typename T>
	void test(std::string message, T expected, T value);
};

#endif
