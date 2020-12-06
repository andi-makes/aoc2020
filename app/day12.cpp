#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 12;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto line : data) {
		}
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto line : data) {
		}
		return count;
	};
}

auto day12 = day<data_t>(day_number, get_input, p1, p2);