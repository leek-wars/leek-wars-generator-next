#include "Test.hpp"
#include "../src/module/LeekModule.hpp"

void Test::test_doc() {

	header("Documentation");

	LeekModule(&manager.vm).generate_doc(std::cout, std::string("doc/Leek_fr.json"));
	std::cout << std::endl;
	// EntityModule().generate_doc(cout, string("doc/Leek_fr.json"));
}
