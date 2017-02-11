#pragma once

#include <string>
#include <fstream>
#include <assert.h>

namespace File {
	std::string toString(const std::string& file) {
		std::fstream f(file);
		assert(f.is_open());
		std::string string;
		std::getline(f, string, '\0');
		f.close();

		return string;
	}
}