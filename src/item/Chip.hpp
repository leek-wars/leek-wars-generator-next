#ifndef CHIP_HPP_
#define CHIP_HPP_

#include "../effect/Attack.hpp"
#include "Item.hpp"

class Chip : public Item {
public:

	int cooldown;
	bool team_cooldown;
	int initial_cooldown;

	Chip(int id, std::string name, int cost, int cooldown, bool team_cooldown, int initial_cooldown, Attack* attack, int template_id);

	virtual ~Chip();

	virtual std::ostream& print(std::ostream& os) const override;
	virtual std::ostream& dump(std::ostream& os, int level) const override;
};

#endif
