#include "ConnexeMap.hpp"

ConnexeMap::ConnexeMap(Map* map) {

	this->map = map;
	cells = new int*[map->sx];
	for (int i = 0; i < map->sx; ++i) {
		cells[i] = new int[map->sy];
		for (int j = 0; j < map->sy; ++j) {
			cells[i][j] = -1;
		}
	}

	int n = 1;

	for (int x = 0; x < map->sx; x++) {
		for (int y = 0; y < map->sy; y++) {
			Cell* c = map->coord[x][y];
			if (c == nullptr) {
				continue;
			}
			int cur_number = 0;
			if (x > 0 and map->coord[x - 1][y] != nullptr and
				map->coord[x - 1][y]->available() == c->available()) {
				cur_number = cells[x - 1][y];
			}

			if (y > 0 and map->coord[x][y - 1] != nullptr and
				map->coord[x][y - 1]->available() == c->available()) {
				if (cur_number == 0) {
					cur_number = cells[x][y - 1];
				} else if (cur_number != cells[x][y - 1]) {
					int target_number = cells[x][y - 1];
					for (int x2 = 0; x2 < map->sx; x2++) {
						for (int y2 = 0; y2 <= y; y2++) {
							if (cells[x2][y2] == target_number)
								cells[x2][y2] = cur_number;
						}
					}
				}
			}
			if (cur_number == 0) {
				cells[x][y] = n;
				n++;
			} else {
				cells[x][y] = cur_number;
			}
		}
	}
}

ConnexeMap::~ConnexeMap() {
	for (int i = 0; i < map->sx; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}

int ConnexeMap::getComponent(Cell* c) {
	return getComponent(c->x, c->y);
}

int ConnexeMap::getComponent(int x, int y) {
	return cells[x - map->min_x][y - map->min_y];
}
