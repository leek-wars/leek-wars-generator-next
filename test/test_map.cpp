#include "Test.hpp"
#include "../benchmark/Benchmark.hpp"

void Test::test_map() {

	header("Map");

	Fight fight;
	Map map(18, 18, 100, {});

	map.print();

	for (int i = 0; i < 100; ++i) {
		int c1 = rand() % 613;
		int c2 = rand() % 613;
		auto path = map.get_path_between(map.cells[c1], map.cells[c2], {});
	}

	int c1 = rand() % 613;
	int c2 = rand() % 613;
	map.cells[c1]->walkable = true;
	map.cells[c2]->walkable = true;
	auto path = map.get_path_between(map.cells[c1], map.cells[c2], {});
	map.draw_path(path, map.int_to_cell(c1), map.int_to_cell(c2));

	int c3 = rand() % 613;
	int c4 = rand() % 613;
	map.cells[c3]->walkable = true;
	map.cells[c4]->walkable = true;
	auto path2 = map.get_path_between(map.cells[c3], map.cells[c4], {});
	map.draw_path(path2, map.int_to_cell(c3), map.int_to_cell(c4));

	header("Pathfinding benchmark");
	Benchmark::pathfinding();
}
