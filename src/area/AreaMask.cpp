#include "AreaMask.hpp"

AreaMask::AreaMask() {}

AreaMask::~AreaMask() {}

std::vector<std::pair<int, int>> AreaMask::generateCircleMask(int min, int max) {

	if (min > max) {
		return {};
	}
	int cellsMin = 0;
	if (min > 0) {
		if (min > 1) {
			cellsMin = 1 + (min - 1) * (4 + 4 * (min - 1)) / 2;
		} else {
			cellsMin = 1;
		}
	}
	int cellsMax = 1;
	if (max > 0) {
		cellsMax = max * (4 + 4 * max) / 2 + 1;
	}
	int nbCells = cellsMax - cellsMin;
	std::vector<std::pair<int, int>> result(nbCells);

	int index = 0;
	if (min == 0) {
		result[0] = { 0, 0 };
		index++;
	}

	for (int size = (min < 1 ? 1 : min); size <= max; size++) {
		for (int i = 0; i < size; i++) {
			result[index] = { i, size - i };
			result[index + 1] = { -i, -(size - i) };
			result[index + 2] = { size - i, -i };
			result[index + 3] = { -(size - i), i };
			index += 4;
		}
	}
	return result;
}
