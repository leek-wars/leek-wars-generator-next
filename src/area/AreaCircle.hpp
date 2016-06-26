/*
 * AreaCircle.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#ifndef SRC_AREA_AREACIRCLE_HPP_
#define SRC_AREA_AREACIRCLE_HPP_

#include "Area.hpp"

class AreaCircle : public Area {
public:

	static std::map<int, std::vector<std::pair<int, int>>> area_cache;

	int radius;

	AreaCircle(Attack* attack, int radius);
	virtual ~AreaCircle();

	virtual std::vector<Cell*> getArea(Cell* launch, Cell* target) const override;

	virtual int getRadius() const override;
};

#endif /* SRC_AREA_AREACIRCLE_HPP_ */
