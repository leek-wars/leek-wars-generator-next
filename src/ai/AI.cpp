/*
 * AI.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: pierre
 */

#include "AI.hpp"
#include <leekscript.h>

AI::AI(std::string code) {

	this->id = 12765;
	this->name = "SuperIA";
	this->code = code;
	this->program = nullptr;
}

AI::~AI() {}

void AI::compile(ls::VM& vm) {

	program = vm.compile(this->code);
}

void AI::execute() {
	if (program != nullptr) {
		program->execute();
	}
}
