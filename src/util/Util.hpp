#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <string>
#include <vector>
#include <queue>

class Util {
public:

	static float random();
	static int rand_int(int min);
	static int rand_int(int min, int max);

	static std::vector<std::string> split(const std::string& string, char separator);
	static std::string toupper(const std::string& string);

	template <typename T>
	static bool contains(const std::vector<T>& vector, const T& element);

	static std::string read_file(std::string file);
};

#endif
