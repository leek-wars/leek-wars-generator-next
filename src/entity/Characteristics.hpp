#ifndef CHARACTERISTICS_HPP_
#define CHARACTERISTICS_HPP_

#include <map>

enum class Characteristic;

class Characteristics {
public:

	std::map<int, int> characteristics;

	Characteristics();
	virtual ~Characteristics();

	int get(Characteristic charac) const;
	void add(const Characteristics& to_add);
	void set(Characteristic key, int value);
	void clear();
	void add(Characteristic key, int value);
};

#endif
