#include "Test.hpp"

void Test::test_map() {

	header("Map");

	Fight fight;
	Map map(18, 18, 50, {});

	map.print();

	auto exe_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10; ++i) {
		int c1 = rand() % 613;
		int c2 = rand() % 613;

		auto path = map.get_path_between(map.cells[c1], map.cells[c2], {});
		std::cout << "path length: " << path.size() << std::endl;
	}

	int c1 = rand() % 613;
	int c2 = rand() % 613;
	auto path = map.get_path_between(map.cells[c1], map.cells[c2], {});
	map.draw_path(path, map.int_to_cell(c1), map.int_to_cell(c2));

	auto exe_end = std::chrono::high_resolution_clock::now();
	long exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(exe_end - exe_start).count();
	double exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	std::cout << "pathfinding: " << exe_time_ms << " ms" << std::endl;
}
