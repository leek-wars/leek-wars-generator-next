#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <string>
#include <vector>
#include <queue>
#include <string.h>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG Util::log() << "[" << "\033[1;34m" << __FILENAME__ << ":" << __LINE__ << "\033[0m" << "] "
#define LOG_I Util::log() << "[" << "\033[1;32m" << __FILENAME__ << ":" << __LINE__ << "\033[0m" << "] "
#define LOG_W Util::log() << "[" << "\033[1;33m" << __FILENAME__ << ":" << __LINE__ << "\033[0m" << "] "
#define LOG_E Util::log() << "[" << "\033[1;31m" << __FILENAME__ << ":" << __LINE__ << "\033[0m" << "] "

class Util {
public:

	static bool log_enabled;
	static std::ostream dummy_stream;

	static std::vector<std::string> split(const std::string& string, char separator);
	static std::string toupper(const std::string& string);
	static std::string tolower(const std::string& string);

	template <typename T>
	static bool contains(const std::vector<T>& vector, const T& element);

	static bool file_exists(std::string file);
	static std::string read_file(std::string file);

	static std::string url_encode(const std::string& value);

	static std::ostream& log() {
		if (log_enabled) return std::cout;
		else return Util::dummy_stream;
	}

	static std::string int_to_hex_color(int color);
};

#endif
