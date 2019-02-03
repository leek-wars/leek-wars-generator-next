#include "RandomGenerator.hpp"
#include <iostream>

void RandomGenerator::seed(long seed) {
	n = seed;
}

int RandomGenerator::getInt(int min, int max) {
	if (max - min + 1 <= 0)
		return 0;
	return min + (int) (getDouble() * (max - min + 1));
}

double RandomGenerator::getDouble() {
	// std::cout << "n = " << n << std::endl;
	n = n * 1103515245 + 12345;
	return (double) ((n / 65536) % 32768 + 32768) / 65536;
}