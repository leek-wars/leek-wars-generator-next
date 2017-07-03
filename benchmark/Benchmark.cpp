#include "Benchmark.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <chrono>
#include "../src/map/Map.hpp"

Benchmark::Benchmark() {}

Benchmark::~Benchmark() {}

void Benchmark::pathfinding() {

	Map map(18, 18, 100, {});

	auto exe_start = chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000; ++i) {
		int c1 = rand() % 613;
		int c2 = rand() % 613;

		map.get_path_between(map.cells[c1], map.cells[c2], {});
	}

	auto exe_end = chrono::high_resolution_clock::now();
	long exe_time_ns = chrono::duration_cast<chrono::nanoseconds>(exe_end - exe_start).count();
	double exe_time_ms = (((double) exe_time_ns / 1000) / 1000);
	cout << "pathfinding 1000 paths: " << exe_time_ms << " ms" << endl;
}
