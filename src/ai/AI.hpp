#ifndef AI_HPP_
#define AI_HPP_

#include <string>
#include <leekscript/src/leekscript.h>

class AI {
public:

	int id;
	std::string name;
	std::string code;
	ls::Program* program;
	bool v1 = false;

	AI(std::string code, std::string name, bool v1 = false);
	virtual ~AI();

	void compile(ls::VM& vm);
	void execute(ls::VM& vm);
};

#endif
