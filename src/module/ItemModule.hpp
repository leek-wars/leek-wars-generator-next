#ifndef CLASS_ITEMMODULE_HPP_
#define CLASS_ITEMMODULE_HPP_

#include <leekscript.h>

class ItemType : public ls::Object_type {
public:
	ItemType() : ls::Object_type(true) {}
	const std::string getName() const { return "Item"; };
	virtual Type* clone() const override { return new ItemType(); }
};

class ItemModule : public ls::Module {
public:
	ItemModule(ls::VM* vm);
	virtual ~ItemModule();
};

#endif
