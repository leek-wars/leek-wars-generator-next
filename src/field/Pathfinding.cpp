#include "Field.hpp"
#include "../effect/Attack.hpp"

bool Field::line_of_sight(const Cell* start, const Cell* end) const {

	if (!end->walkable) return false;

	return line_of_sight_ignored(start, end, {});
}

bool Field::line_of_sight_attack(const Cell* start, const Cell* end, const Attack* attack, std::vector<const Cell*> ignored) const {

	if (!end->walkable) return false;

	bool needLos = attack == nullptr ? true : attack->need_los;
	if (!needLos) return true;

	return line_of_sight_ignored(start, end, ignored);
}

bool Field::line_of_sight_ignored(const Cell* start, const Cell* end, std::vector<const Cell*> ignored) const {

	auto check_cell = [&](Cell* cell) {
		if (cell == nullptr || !cell->walkable) return false;
		if (cell->available() || cell == end) return true;
		return find(ignored.begin(), ignored.end(), cell) != ignored.end();
	};
	int x1 = start->x - min_x;
	int y1 = start->y - min_y;
	int a = abs(start->y - end->y);
	int b = abs(start->x - end->x);
	int dx = copysign(1, end->x - start->x);
	int dy = copysign(1, end->y - start->y);
	float h = 0;
	float y = 0;
	if (b > 0) {
		float d = a / b / 2;
		for (int x = 0; x < b; ++x) {
			y = 0.5 + (x * 2 + 1) * d;
			for (int i = 0; i < ceil(y) - h; i++) {
				if (!check_cell(coord[y1 + (h + i) * dy][x1])) return false;
			}
			h = floor(y + 2 * std::numeric_limits<float>::epsilon());
			x1 += dx;
		}
	}
	for (int i = 0; i < a + 1 - h; i++) {
		if (!check_cell(coord[y1 + (h + i) * dy][x1])) return false;
	}
	return true;
}

std::vector<const Cell*> Field::get_path_between(Cell* start, const Cell* end, std::vector<const Cell*> ignored_cells) const {
	if (start == nullptr || end == nullptr) {
		return {};
	}
	return get_path(start, {end}, ignored_cells);
}

std::vector<const Cell*> Field::get_path(Cell* c1, std::vector<const Cell*> end_cells, std::vector<const Cell*> ignored) const {

	if (c1 == nullptr or end_cells.size() == 0) {
		// cout << "[path] invalid cells" << endl;
		return {};
	}
	if (find(end_cells.begin(), end_cells.end(), c1) != end_cells.end()) {
		// cout << "[path] already arrived" << endl;
		return {};
	}

	for (auto& c : cells) {
		c->visited = false;
		c->closed = false;
		c->cost = std::numeric_limits<unsigned short>::max();
	}

	std::vector<Cell*> open;
	NodeComparator comp;

	c1->cost = 0;
	c1->weight = 0;
	c1->visited = true;
	open.push_back(c1);
	std::push_heap(open.begin(), open.end(), comp);

	while (open.size() > 0) {

		std::pop_heap(open.begin(), open.end(), comp);
		auto u = open.back();
		open.pop_back();
		u->closed = true;

		if (find(end_cells.begin(), end_cells.end(), u) != end_cells.end()) {
			std::vector<const Cell*> result;
			int s = u->cost;
			while (s-- >= 0) {
				result.push_back(u);
				u = u->parent;
			}
			std::reverse(result.begin(), result.end());
			return result;
		}

		for (auto& c : get_cells_around(u)) {

			if (c->closed) continue;
			if (c->entity != nullptr and find(ignored.begin(), ignored.end(), c) == ignored.end() and find(end_cells.begin(), end_cells.end(), c) == end_cells.end()) continue;

			if (!c->visited or u->cost + 1 < c->cost) {
				c->cost = u->cost + 1;
				c->weight = c->cost + get_distance_float(c, end_cells);
				c->parent = u;
				if (!c->visited) {
					open.push_back(c);
					std::push_heap(open.begin(), open.end(), comp);
					c->visited = true;
				}
			}
		}
	}
	// cout << "[path] no path found!" << endl;
	return {};
}
