#include "RandomGenerator.hpp"
#include <iostream>
#include "../util/Util.hpp"

RandomGenerator::RandomGenerator() {
	n = 0;
}
void RandomGenerator::seed(long seed) {
	// LOG << "Random seed = " << seed << std::endl;
	n = seed;
}

int RandomGenerator::getInt(int min, int max) {
	if (max - min + 1 <= 0)
		return 0;
	return min + (int) (getDouble() * (max - min + 1));
}

double RandomGenerator::getDouble() {
	// LOG << "n = " << n << std::endl;
	n = n * 1103515245 + 12345;
	return (double) ((n / 65536) % 32768 + 32768) / 65536;
}