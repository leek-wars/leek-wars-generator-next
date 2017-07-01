#include "Util.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

std::ostream Util::dummy_stream(0);
bool Util::log_enabled = true;

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

std::string Util::toupper(const std::string& string) {
	std::string result = string;
	std::for_each(result.begin(), result.end(), [](char& in) {
		in = ::toupper(in);
	});
	return result;
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

string Util::url_encode(const string& value) {
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;
	for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		string::value_type c = (*i);
		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}
		// Any other characters are percent-encoded
		escaped << uppercase;
		escaped << '%' << std::setw(2) << int((unsigned char) c);
		escaped << nouppercase;
	}
	return escaped.str();
}
