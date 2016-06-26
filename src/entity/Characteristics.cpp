#include "Characteristics.hpp"

Characteristics::Characteristics() {}

Characteristics::~Characteristics() {}

int Characteristics::get(Characteristic characteristic) const {
	try {
		return characteristics.at((int) characteristic);
	} catch (exception& e) {
		return 0;
	}
}

void Characteristics::add(const Characteristics& to_add) {
	for (auto c : to_add.characteristics) {
		add((Characteristic) c.first, c.second);
	}
}

void Characteristics::set(Characteristic key, int value) {
	characteristics[(int) key] = value;
}

void Characteristics::clear() {
	characteristics.clear();
}

void Characteristics::add(Characteristic key, int value) {
	characteristics[(int) key] += value;
}
