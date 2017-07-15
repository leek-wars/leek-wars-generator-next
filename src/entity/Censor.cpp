#include "Censor.hpp"
#include <iostream>
#include "../util/Util.hpp"

void Censor::load(std::string forbidden_words_file) {
	auto lines = Util::split(Util::read_file(forbidden_words_file), '\n');
	for (const auto& line : lines) {
		words.insert(Util::tolower(line));
	}
}

std::string Censor::censor(const std::string& message) {
	size_t prev = 0;
	size_t pos;
	auto new_message = message;
	// TODO use a regex to have all the symbols possible
	while ((pos = new_message.find_first_of(".:;!?'\"\\[](){}-_*~  	", prev)) != std::string::npos) {
		if (pos > prev) {
			auto word = Util::tolower(new_message.substr(prev, pos - prev));
			if (words.find(word) != words.end()) {
				std::fill(new_message.begin() + prev, new_message.begin() + pos, '*');
			}
		}
		prev = pos + 1;
	}
	if (prev < new_message.length()) {
		auto word = Util::tolower(new_message.substr(prev));
		if (words.find(word) != words.end()) {
			std::fill(new_message.begin() + prev, new_message.end(), '*');
		}
	}
	return new_message;
}
