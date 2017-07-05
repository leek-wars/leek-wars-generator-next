#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <string>
#include "Item.hpp"

class Weapon : public Item {
public:

	Weapon(int id, std::string name, int cost, Attack* attack, int template_id);
	virtual ~Weapon();

	int getTemplateID() const;

	virtual std::ostream& print(std::ostream& os) const override;
};

#endif
