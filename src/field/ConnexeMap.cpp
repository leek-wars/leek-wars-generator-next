#include "ConnexeMap.hpp"

ConnexeMap::ConnexeMap(Field* field) {

	this->field = field;
	cells = new int*[field->sx];
	for (int i = 0; i < field->sx; ++i) {
		cells[i] = new int[field->sy];
		for (int j = 0; j < field->sy; ++j) {
			cells[i][j] = -1;
		}
	}

	int n = 1;

	for (auto& c : field->cells) {
		int x = c->x - field->min_x;
		int y = c->y - field->min_y;

		int cur_number = 0;
		if (x > 0 and field->coord[x - 1][y] != nullptr and
			field->coord[x - 1 ][y]->available() == c->available()) {
			cur_number = cells[x - 1][y];
		}

		if (y > 0 and field->coord[x][y - 1] != nullptr and
			field->coord[x][y - 1]->available() == c->available()) {
			if (cur_number == 0) {
				cur_number = cells[x][y - 1];
			} else if (cur_number != cells[x][y - 1]) {
				int target_number = cells[x][y - 1];
				for (int x2 = 0; x2 < field->sx; x2++) {
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

ConnexeMap::~ConnexeMap() {
	for (int i = 0; i < field->sx; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}

int ConnexeMap::getComponent(Cell* c) {
	return getComponent(c->x, c->y);
}

int ConnexeMap::getComponent(int x, int y) {
	return cells[x - field->min_x][y - field->min_y];
}
