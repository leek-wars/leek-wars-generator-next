#ifndef CLASS_ITEMMODULE_HPP_
#define CLASS_ITEMMODULE_HPP_

#include <leekscript.h>

class ItemType : public ls::ObjectRawType {
public:
	const std::string getName() const { return "Item"; };
};


class ItemModule : public ls::Module {
public:
	ItemModule();
	virtual ~ItemModule();
};

#endif
