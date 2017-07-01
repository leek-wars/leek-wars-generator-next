#include "AI.hpp"
#include "../module/EntityModule.hpp"
#include "../util/Util.hpp"

AI::AI(std::string code, std::string ai_name, bool v1) {
	this->id = 12765;
	this->name = ai_name;
	this->code = code;
	this->program = nullptr;
	this->v1 = v1;
}

AI::~AI() {
	if (program != nullptr) {
		delete program;
	}
}

void AI::compile(ls::VM& vm, ls::VM& vm_v1) {

	ls::VM::current_vm = v1 ? &vm_v1 : &vm;
	program = new ls::Program(code, name);
	auto result = program->compile(v1 ? vm_v1 : vm, "{}");

	if (result.lexical_errors.size()) {
		LOG_W << result.lexical_errors.size() << " lexical error(s) in AI " << name << std::endl;
		for (const auto& e : result.lexical_errors) {
			LOG_W << "Line " << e.line << ": " << e.message() << std::endl;
		}
		valid = false;
	}
	if (result.syntaxical_errors.size()) {
		LOG_W << result.syntaxical_errors.size() << " syntaxic error(s) in AI " << name << std::endl;
		for (const auto& e : result.syntaxical_errors) {
			LOG_W << "Line " << e.token->location.start.line << ": " << e.message() << std::endl;
		}
		valid = false;
	}

	if (result.semantical_errors.size()) {
		LOG_W << result.semantical_errors.size() << " semantic error(s) in AI " << name << std::endl;
		bool first = true;
		for (const auto& e : result.semantical_errors) {
			if (!first) std::cout << std::endl;
			LOG_W << e.file << ":" << e.location.start.line << ": " << e.underline_code << std::endl << "   ▶ " << e.message() << std::endl;
			first = false;
		}
		valid = false;
	}

	LOG << "AI [" << name << "] : ";
	if (result.lexical_errors.size() == 0 && result.syntaxical_errors.size() == 0) {
		program->print(Util::log(), true);
		LOG << std::endl;
	} else {
		LOG << "ERROR" << std::endl;
	}
}

void AI::execute(ls::VM& vm, ls::VM& vm_v1) {
	if (program != nullptr && valid) {
		ls::VM::current_vm = v1 ? &vm_v1 : &vm;
		program->execute(*ls::VM::current_vm);
	} else {
		LOG_W << "AI " << name << " invalid, excution skipped!" << std::endl;
	}
}
