#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <leekscript/src/leekscript.h>
#include "../effect/Attack.hpp"

class Item : public ls::LSObject {
public:

	int id;
	std::string name;
	int cost;
	std::unique_ptr<Attack> attack;

	Item(int id, std::string& name, int cost, Attack* attack);
	virtual ~Item();

	virtual std::ostream& print(std::ostream&) const = 0;
};

#endif
