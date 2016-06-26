/*
 * AreaLaserLine.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#ifndef SRC_AREA_AREALASERLINE_HPP_
#define SRC_AREA_AREALASERLINE_HPP_

#include "Area.hpp"

class AreaLaserLine: public Area {
public:
	AreaLaserLine(Attack* attack);
	virtual ~AreaLaserLine();

	virtual std::vector<Cell*> getArea(Cell* launch, Cell* target) const override;

	virtual int getRadius() const override;
};

#endif /* SRC_AREA_AREALASERLINE_HPP_ */
