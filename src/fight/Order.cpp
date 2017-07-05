#include <algorithm>
#include "Order.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Summon.hpp"

void Order::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void Order::addSummon(Entity* owner, Summon* summon) {
	auto i = std::find(entities.begin(), entities.end(), owner);
	if (i == entities.end()) {
		return;
	}
	entities.insert(i + 1, summon);
}

void Order::addEntity(unsigned int index, Entity* entity) {
	entities.insert(entities.begin() + index, entity);
	if (index <= position) {
		position++;
	}
}

void Order::removeEntity(Entity* entity) {
	auto i = find(entities.begin(), entities.end(), entity);
	if (i == entities.end()) {
		return;
	}
	if (distance(entities.begin(), i) <= position) {
		position--;
	}
	entities.erase(i);
	if (position < 0) {
		position = entities.size() - 1;
	}
}

Entity* Order::current() {
	if (position >= entities.size()) {
		return nullptr;
	}
	return entities[position];
}

int Order::getTurn() {
	return turn;
}

int Order::getEntityTurnOrder(Entity* e) {
	return distance(entities.begin(), find(entities.begin(), entities.end(), e)) + 1;
}

bool Order::next() {
	position++;
	if (position >= entities.size()) {
		turn++;
		position = position % entities.size();
		return true;
	}
	return false;
}

Entity* Order::getNextPlayer() {
	return entities[(position + 1) % entities.size()];
}

Entity* Order::getPreviousPlayer() {
	int p = position - 1;
	if (p < 0)
		p += entities.size();
	return entities[p];
}

int Order::getPosition() const {
	return position;
}

std::ostream& operator << (std::ostream& os, Order& order) {
	os << "[";
	for (Entity* e : order.entities) {
		os << e->name << ", ";
	}
	os << "], pos = " << order.getPosition() << endl;
	return os;
}
