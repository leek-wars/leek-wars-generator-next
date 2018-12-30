#ifndef CLASS_CELLMODULE_HPP_
#define CLASS_CELLMODULE_HPP_

#include <leekscript.h>
class Cell;
class LSEntity;

class CellType : public ls::Object_type {
public:
	virtual const std::string getName() const override { return "cell"; };
	virtual std::string clazz() const override { return "Cell"; };
};

class CellModule : public ls::Module {
public:
	CellModule();
	virtual ~CellModule();

	static const ls::LSClass* cell_clazz;
	static const std::shared_ptr<CellType> raw_type;
	static const ls::Type type;
	static const ls::Type const_type;
	static const ls::Type array_type;
};

bool cell__isEmptyCell(const ls::LSValue* cell);
bool cell__isLeek(const ls::LSValue* cell);
bool cell__isObstacle(const ls::LSValue* cell);
ls::LSValue* cell__getCellX(const ls::LSValue* cell);
ls::LSValue* cell__getCellY(const ls::LSValue* cell);
int cell__getLeekOnCell(const ls::LSValue* cell);
int cell__getCellContent(const ls::LSValue* cell);

#endif
