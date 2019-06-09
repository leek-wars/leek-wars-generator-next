#include "Test.hpp"
#include "../src/module/WeaponModule.hpp"

void Test::test_types() {

	header("Types");

	std::cout << ls::Type::any->distance(WeaponModule::type) << std::endl;
	std::cout << WeaponModule::type->distance(ls::Type::any) << std::endl;
}
