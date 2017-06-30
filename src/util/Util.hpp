#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <string>
#include <vector>
#include <queue>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG std::cout << "[" << "\033[1;34m" << __FILENAME__ << ":" << __LINE__ << "\033[0m" << "] "

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

	static std::string url_encode(const std::string& value);
};

#endif
