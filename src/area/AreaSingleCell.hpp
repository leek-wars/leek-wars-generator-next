/*
 * AreaSingleCell.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#ifndef SRC_AREA_AREASINGLECELL_HPP_
#define SRC_AREA_AREASINGLECELL_HPP_

#include "Area.hpp"

class AreaSingleCell: public Area {
public:
	AreaSingleCell(Attack* attack);
	virtual ~AreaSingleCell();

	virtual std::vector<Cell*> getArea(Cell* launch, Cell* target) const override;

	virtual int getRadius() const override;
};

#endif /* SRC_AREA_AREASINGLECELL_HPP_ */
