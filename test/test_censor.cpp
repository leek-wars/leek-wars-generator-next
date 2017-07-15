#include "Test.hpp"
#include "../src/entity/Censor.hpp"

void Test::test_censor() {

	header("Censorship");

	Censor censor;
	censor.load("data/forbidden_words.txt");

	auto test_censor_case = [&](const std::string& sentence, const std::string& result) {
		test(std::string("censor('") + sentence + std::string("')"), result, censor.censor(sentence));
	};

	test_censor_case("fuck", "****");
	test_censor_case("you bastard", "you *******");
	test_censor_case("You are a fucking moron!!", "You are a ******* *****!!");
	test_censor_case("	Shit-, go_FuCk_ yourself", "	****-, go_****_ yourself");
}
