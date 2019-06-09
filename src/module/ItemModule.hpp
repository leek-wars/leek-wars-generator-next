#ifndef CLASS_ITEMMODULE_HPP_
#define CLASS_ITEMMODULE_HPP_

#include <leekscript.h>

class ItemType : public ls::Object_type {
public:
	const std::string getName() const { return "Item"; };
};

class ItemModule : public ls::Module {
public:
	ItemModule(ls::VM* vm);
	virtual ~ItemModule();
};

#endif
