#ifndef CENSOR_HPP
#define CENSOR_HPP

#include <string>
#include <set>

class Censor {
public:

	std::set<std::string> words;

	void load(std::string forbidden_words_file);
	std::string censor(const std::string& message);
};

#endif
