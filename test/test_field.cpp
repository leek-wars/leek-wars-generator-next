#include "Test.hpp"
#include "../benchmark/Benchmark.hpp"

void Test::test_field() {

	header("Field");

	Fight fight;
	Field field(18, 18, 100, {});

	field.print();

	for (int i = 0; i < 100; ++i) {
		int c1 = rand() % 613;
		int c2 = rand() % 613;
		auto path = field.get_path_between(field.cells[c1], field.cells[c2], {});
	}

	int c1 = rand() % 613;
	int c2 = rand() % 613;
	field.cells[c1]->walkable = true;
	field.cells[c2]->walkable = true;
	auto path = field.get_path_between(field.cells[c1], field.cells[c2], {});
	field.draw_path(path, field.int_to_cell(c1), field.int_to_cell(c2));

	int c3 = rand() % 613;
	int c4 = rand() % 613;
	field.cells[c3]->walkable = true;
	field.cells[c4]->walkable = true;
	auto path2 = field.get_path_between(field.cells[c3], field.cells[c4], {});
	field.draw_path(path2, field.int_to_cell(c3), field.int_to_cell(c4));
}

void Test::test_pathfinding() {

	header("Pathfinding benchmark");

	Field field(17, 17, 60, {});

	auto exe_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000; ++i) {
		int c1 = rand() % field.cells.size();
		int c2 = rand() % field.cells.size();
		field.get_path_between(field.cells[c1], field.cells[c2], {});
	}

	auto exe_end = std::chrono::high_resolution_clock::now();
	long exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(exe_end - exe_start).count();
	double exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	std::cout << "pathfinding 1000 paths: " << exe_time_ms << " ms" << std::endl;
}

void Test::test_line_of_sight() {

	header("Pathfinding line_of_sight");

	Field field(17, 17, 60, {});
	auto cells = field.cells.size();
	auto samples = 1000000;

	auto exe_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < samples; ++i) {
		int c1 = rand() % cells;
		int c2 = rand() % cells;
		field.line_of_sight(field.cells[c1], field.cells[c2]);
	}

	auto exe_end = std::chrono::high_resolution_clock::now();
	long exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(exe_end - exe_start).count();
	double exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	std::cout << std::to_string(samples) << " lines of sight: " << exe_time_ms << " ms" << std::endl;
}
