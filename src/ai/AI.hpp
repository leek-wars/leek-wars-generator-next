#ifndef AI_HPP_
#define AI_HPP_

#include <string>
#include <leekscript.h>

class AI {
public:

	int id;
	std::string name;
	std::string code;
	ls::Program* program;
	bool v1 = false;
	bool valid = true;

	AI(std::string code, std::string name, bool v1 = false);
	virtual ~AI();

	void compile(ls::VM& vm, ls::VM& vm_v1);
	void execute(ls::VM& vm, ls::VM& vm_v1);
};

#endif
