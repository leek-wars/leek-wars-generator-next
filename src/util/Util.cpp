#include "Util.hpp"

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;

float Util::random() {
	return (float) rand() / RAND_MAX;
}

int Util::rand_int(int max) {
	return rand() % max;
}

int Util::rand_int(int min, int max) {
	return min + rand() % (max - min + 1);
}

vector<string> Util::split(const string& s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

template <typename T>
bool Util::contains(const std::vector<T>& vector, const T& element) {
	return find(vector.begin(), vector.end(), element) != vector.end();
}

string Util::read_file(string file) {
	ifstream ifs(file.data());
	string content = string((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
	ifs.close();
	return content;
}

