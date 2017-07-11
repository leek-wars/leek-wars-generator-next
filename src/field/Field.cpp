#include <iostream>
#include <math.h>
#include <limits>
#include <type_traits>
#include <algorithm>
#include <queue>
#include <set>
#include "Field.hpp"
#include "../util/Util.hpp"
#include "ConnexeMap.hpp"
#include "../effect/Attack.hpp"
#include "../entity/Team.hpp"

Field::Field(int width, int height, int obstacles_count, const std::vector<Team*>& teams) {

	this->width = width;
	this->height = height;

	nb_cells = (width * 2 - 1) * height - (width - 1);

	for (int i = 0; i < nb_cells; i++) {
		auto c = new Cell(this, i);
		cells.push_back(c);
		if (min_x == -1 || c->x < min_x) min_x = c->x;
		if (max_x == -1 || c->x > max_x) max_x = c->x;
		if (min_y == -1 || c->y < min_y) min_y = c->y;
		if (max_y == -1 || c->y > max_y) max_y = c->y;
	}

	sx = max_x - min_x + 1;
	sy = max_y - min_y + 1;

	coord.resize(sx);
	for (int i = 0; i < sx; ++i) {
		coord[i].resize(sy, nullptr);
	}
	for (int i = 0; i < nb_cells; i++) {
		auto c = cells[i];
		coord[c->x - min_x][c->y - min_y] = c;
	}
	generate(obstacles_count, teams);
}

Field::~Field() {
	for (auto& c : cells) {
		delete c;
	}
}

void Field::generate(int obstacles_count, const std::vector<Team*>& teams) {

	int nb = 0;
	bool valid = false;

	while (!valid && nb < 64) {

		valid = true;
		type = Util::rand_int(0, 4);
		obstacles.clear();

		for (int i = 0; i < obstacles_count; i++) {
			auto c = get_cell(Util::rand_int(nb_cells));
			if (c != nullptr && c->available()) {
				int size = Util::rand_int(1, 2);
				int type = Util::rand_int(0, 2);
				if (size == 2) {
					Cell* c2 = get_cell_by_direction(c, Direction::EAST);
					Cell* c3 = get_cell_by_direction(c, Direction::SOUTH);
					Cell* c4 = get_cell_by_direction(c3, Direction::EAST);
					if (c2 == nullptr || c3 == nullptr || c4 == nullptr
						|| !c2->available() || !c3->available() || !c4->available())
						size = 1;
					else {
						c2->setObstacle(0, -1);
						c3->setObstacle(0, -1);
						c4->setObstacle(0, -1);
						obstacles.push_back(c2);
						obstacles.push_back(c3);
						obstacles.push_back(c4);
					}
				}
				c->setObstacle(type, size);
				obstacles.push_back(c);
			}
		}
		ConnexeMap cm(this);
		std::vector<Entity*> entities;

		// Set entities positions
		for (unsigned t = 0; t < teams.size(); ++t) {
			for (Entity* e : teams[t]->entities) {
				Cell* c;
				if (teams.size() == 2) { // 2 teams : 2 sides
					c = get_random_cell(t == 0 ? 1 : 4);
				} else { // 2+ teams : random
					c = get_random_cell();
				}
				if (c == nullptr) {
					// Enable to find a cell, rebuild the map
					valid = false;
					break;
				}
				c->setEntity(e);
				entities.push_back(e);
			}
		}
		if (!valid) break;

		// Check paths
		if (entities.size() > 0) {
			int component = cm.getComponent(entities[0]->cell);
			for (unsigned i = 1; i < entities.size(); i++) {
				if (component != cm.getComponent(entities[i]->cell)) {
					valid = false;
					break;
				}
			}
		}
		nb++;
	}
	assert(valid || "Invalid map! Too much obstacles?");
}

Cell* Field::get_cell(int id) {
	if (id < 0 or id >= (int) cells.size()) {
		return nullptr;
	}
	return cells[id];
}

Cell* Field::get_cell(int x, int y) {
	return coord[x - min_x][y - min_y];
}

std::vector<Cell*> Field::get_obstacles() {
	return obstacles;
}

Cell* Field::get_random_cell() {
	Cell* c = nullptr;
	int security = 0;
	do {
		c = get_cell(Util::rand_int(nb_cells));
	} while (!c->available() && security++ < 512);
	return c;
}

Cell* Field::get_random_cell(int part) {
	Cell* c = nullptr;
	int security = 0;
	do {
		int y = Util::rand_int(height - 1);
		int x = Util::rand_int(width / 4);
		int cellid = y * (width * 2 - 1);
		cellid += (part - 1) * width / 4 + x;
		c = get_cell(cellid);
	} while (!c->available() && security++ < 512);
	return c;
}

bool Field::can_use_attack(const Cell* caster, const Cell* target, const Attack* attack) const {

	if (target == nullptr || caster == nullptr) {
		return false;
	}
	if (attack->launch_type == LaunchType::CIRCLE) {

		int dist = get_cell_distance(caster, target);
		if (attack->min_range > dist || attack->max_range < dist) {
			return false;
		}
		return line_of_sight_attack(caster, target, attack, {caster});

	} else if (attack->launch_type == LaunchType::LINE) {

		if (caster->x != target->x and caster->y != target->y) {
			return false;
		}
		int dist = get_cell_distance(caster, target);
		if (attack->min_range > dist || attack->max_range < dist) {
			return false;
		}
		return line_of_sight_attack(caster, target, attack, {caster});
	}
	return false;
}

int Field::get_distance2(const Cell* c1, const Cell* c2) const {
	return (c1->x - c2->x) * (c1->x - c2->x) + (c1->y - c2->y) * (c1->y - c2->y);
}

float Field::get_distance2_float(const Cell* c1, const Cell* c2) const {
	return (c1->x - c2->x) * (c1->x - c2->x) + (c1->y - c2->y) * (c1->y - c2->y);
}

float Field::get_distance2_float(const Cell* c1, const std::vector<const Cell*> cells) const {
	float dist = -1;
	for (const auto& c2 : cells) {
		auto d = get_distance2_float(c1, c2);
		if (dist == -1 or d < dist) {
			dist = d;
		}
	}
	return dist;
}

double Field::get_distance(const Cell* c1, const Cell* c2) const {
	return sqrt(get_distance2(c1, c2));
}

float Field::get_distance_float(const Cell* c1, const Cell* c2) const {
	return sqrt(get_distance2_float(c1, c2));
}

float Field::get_distance_float(const Cell* c1, const std::vector<const Cell*> cells) const {
	float dist = -1;
	for (const auto& c2 : cells) {
		auto d = get_distance(c1, c2);
		if (dist == -1 or d < dist) {
			dist = d;
		}
	}
	return dist;
}

int Field::get_cell_distance(const Cell* c1, const Cell* c2) const {
	return abs(c1->x - c2->y) + abs(c1->y - c2->y);
}

int Field::get_cell_distance(const Cell* c1, const std::vector<const Cell*> cells) const {
	int dist = -1;
	for (const Cell* c2 : cells) {
		int d = get_cell_distance(c1, c2);
		if (dist == -1 || d < dist) {
			dist = d;
		}
	}
	return dist;
}

const std::vector<Cell*> Field::get_cells_around(const Cell* const c) const {
	std::vector<Cell*> cells;
	if (c->y > min_y) {
		auto v = coord[c->x - min_x][c->y - min_y - 1];
		if (v != nullptr and v->walkable) {
			cells.push_back(v);
		}
	}
	if (c->x < max_x) {
		auto v = coord[c->x - min_x + 1][c->y - min_y];
		if (v != nullptr and v->walkable) {
			cells.push_back(v);
		}
	}
	if (c->x > min_x) {
		auto v = coord[c->x - min_x - 1][c->y - min_y];
		if (v != nullptr and v->walkable) {
			cells.push_back(v);
		}
	}
	if (c->y < max_y) {
		auto v = coord[c->x - min_x][c->y - min_y + 1];
		if (v != nullptr and v->walkable) {
			cells.push_back(v);
		}
	}
	return cells;
}

Cell* Field::get_cell_by_direction(Cell* cell, Direction dir) {
	if (cell == nullptr) {
		return nullptr;
	}
	if (dir == Direction::NORTH and cell->north) {
		return (Cell*) int_to_cell(cell->id - cell->field->width + 1);
	} else if (dir == Direction::WEST && cell->west) {
		return (Cell*) int_to_cell(cell->id - cell->field->width);
	} else if (dir == Direction::EAST && cell->east) {
		return (Cell*) int_to_cell(cell->id + cell->field->width);
	} else if (dir == Direction::SOUTH && cell->south) {
		return (Cell*) int_to_cell(cell->id + cell->field->width - 1);
	}
	return nullptr;
}

const Cell* Field::int_to_cell(int cell) {
	if (cell < 0 or (size_t) cell >= cells.size()) return nullptr;
	return cells[cell];
}

void Field::print() const {
	std::ostringstream oss;
	oss << "Field: " << std::endl;
	for (int x = 0; x < sx; ++x) {
		for (int y = 0; y < sy; ++y) {
			auto c = coord[y][x];
			if (c == nullptr) {
				oss << "  ";
			} else if (c->walkable) {
				oss << "░░";
			} else {
				oss << "▓▓";
			}
		}
		oss << std::endl;
	}
	LOG << oss.str();
}

void Field::draw_path(const std::vector<const Cell*> path, const Cell* cell1, const Cell* cell2) const {

	std::ostringstream oss;
	oss << "Draw path: [";
	for (const auto& c : path) oss << c->id << " -> ";
	oss << "] length " << path.size() << std::endl;

	for (int x = 0; x < sx; ++x) {
		for (int y = 0; y < sy; ++y) {
			auto c = coord[y][x];
			auto it = find(path.begin(), path.end(), c);
			if (c == nullptr) {
				oss << "  ";
			} else if (c == cell1) {
				oss << "S ";
			} else if (c == cell2) {
				oss << "E ";
			} else if (it != path.end()) {
				oss << (char)('a' + (distance(path.begin(), it) % 26) ) << ' ';
			} else if (c->walkable) {
				oss << "░░";
			} else {
				oss << "▓▓";
			}
		}
		oss << std::endl;
	}
	LOG << oss.str();
}

Json Field::json() const {
	Json obstacles_json;
	for (auto c : obstacles) {
		obstacles_json[std::to_string(c->id)] = std::vector<int>{ c->obstacle, c->obstacle_size };
	}
	return {
		{"type", 1},
		{"obstacles", obstacles_json},
		{"width", width},
		{"height", height}
	};
}

std::ostream& operator << (std::ostream& os, const Field& map) {
	os << "[" << map.width << " × " << map.height << "]";
	return os;
}
