#include "Test.hpp"
#include "../benchmark/Benchmark.hpp"

void Test::test_field() {

	header("Field > Pathfinding");
	Util::log_enabled = true;

	Fight fight;
	fight.manager = &manager;
	Field field(&fight, 17, 17, 120, {});
	int cells = field.cells.size();

	// Display one interesting path
	std::vector<const Cell*> path;
	int c1, c2;
	do {
		c1 = rand() % cells;
		c2 = rand() % cells;
		field.cells[c1]->walkable = true;
		field.cells[c2]->walkable = true;
		path = field.get_path_between(field.cells[c1], field.cells[c2], {});
	} while (path.size() < 30);
	field.draw_path(path, field.int_to_cell(c1), field.int_to_cell(c2));

	// Benchmark multiple paths
	Util::log_enabled = false;
	int samples = 1000;
	auto exe_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < samples; ++i) {
		int c1 = rand() % cells;
		int c2 = rand() % cells;
		field.get_path_between(field.cells[c1], field.cells[c2], {});
	}

	auto exe_end = std::chrono::high_resolution_clock::now();
	long exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(exe_end - exe_start).count();
	double exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	std::cout << BOLD << samples << END_STYLE << " pathfindings in " << BOLD << exe_time_ms << " ms" << END_STYLE << std::endl;

	header("Field > lineOfSight");

	samples = 1000000;
	exe_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < samples; ++i) {
		int c1 = rand() % cells;
		int c2 = rand() % cells;
		field.line_of_sight(field.cells[c1], field.cells[c2]);
	}

	exe_end = std::chrono::high_resolution_clock::now();
	exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(exe_end - exe_start).count();
	exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	std::cout << BOLD << samples << END_STYLE << " lines of sight in " << BOLD << exe_time_ms << " ms" << END_STYLE << std::endl;
}
