#ifndef SRC_AREA_AREAMASK_HPP_
#define SRC_AREA_AREAMASK_HPP_

#include <vector>

class AreaMask {
public:
	AreaMask();
	virtual ~AreaMask();

	static std::vector<std::pair<int, int>> generateCircleMask(int min, int max);
};

#endif
