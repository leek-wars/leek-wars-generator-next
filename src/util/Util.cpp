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

std::ostream Util::dummy_stream(0);
bool Util::log_enabled = true;

std::vector<std::string> Util::split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
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

std::string Util::tolower(const std::string& string) {
	std::string result = string;
	std::for_each(result.begin(), result.end(), [](char& in) {
		in = ::tolower(in);
	});
	return result;
}

template <typename T>
bool Util::contains(const std::vector<T>& vector, const T& element) {
	return find(vector.begin(), vector.end(), element) != vector.end();
}

std::string Util::read_file(std::string file) {
	std::ifstream ifs(file.data());
	std::string content = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();
	return content;
}

std::string Util::url_encode(const std::string& value) {
	std::ostringstream escaped;
	escaped.fill('0');
	escaped << std::hex;
	for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		std::string::value_type c = (*i);
		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}
		// Any other characters are percent-encoded
		escaped << std::uppercase;
		escaped << '%' << std::setw(2) << int((unsigned char) c);
		escaped << std::nouppercase;
	}
	return escaped.str();
}

std::string Util::int_to_hex_color(int color) {
	std::stringstream stream;
	stream << std::hex << color;
	return stream.str();
}
