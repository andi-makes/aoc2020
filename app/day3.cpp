#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 3;

	int get_trees(const std::vector<std::string>& input, int incx, int incy) {
		int width = input[0].length();
		int index = 0;
		int trees = 0;
		for (int i = 0; i < input.size(); i += incy) {
			if (input[i][index % width] == '#') {
				++trees;
			}
			index += incx;
		}

		return trees;
	}

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int width = data[0].length();
		int index = 0;
		int trees = 0;
		for (int i = 0; i < data.size(); i += 1) {
			if (data[i][index % width] == '#') {
				++trees;
			}
			index += 3;
		}

		return trees;
	};

	// auto p1 = [](const data_t& data) -> int64_t {
	// 	return get_trees(data, 3, 1);
	// };

	auto p2 = [](const data_t& data) -> int64_t {
		return get_trees(data, 1, 1) * get_trees(data, 3, 1) *
			   get_trees(data, 5, 1) * get_trees(data, 7, 1) *
			   get_trees(data, 1, 2);
	};
}

day<data_t> day3 = day<data_t>(day_number, get_input, p1, p2);