#ifndef CHIP_HPP_
#define CHIP_HPP_

#include "../effect/Attack.hpp"
#include "Item.hpp"

enum ChipID {
	TELEPORTATION = 12121212
};

class Chip : public Item {
public:

	int cooldown;
	bool team_cooldown;
	int initial_cooldown;

	Chip(int id, std::string name, int cost, int cooldown, bool team_cooldown, int initial_cooldown, Attack* attack);

	virtual ~Chip();

	virtual std::ostream& print(std::ostream& os) const override;
};

#endif
