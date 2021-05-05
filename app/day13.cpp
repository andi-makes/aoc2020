#include "registry.h"

namespace {
	using data_t			 = std::vector<int>;
	constexpr int day_number = 13;

	std::map<int, int> timings;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		int buf;
		input >> buf;
		data.push_back(buf);
		std::string buffer;
		int i = 0;
		while (std::getline(input, buffer, ',')) {
			if (buffer[0] == 'x') {
				++i;
				continue;
			}
			timings.insert({ std::stoi(buffer), i });
			++i;
			data.push_back(std::stoi(buffer));
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int count		 = 0;
		int minutes_left = data[0];
		for (auto line : data) {
			if (line - (data[0] % line) < minutes_left) {
				count		 = line;
				minutes_left = line - (data[0] % line);
			}
		}
		return count * minutes_left;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto set : timings) {
			fmt::print("(z + {}) mod {} = 0,", set.second, set.first);
		}
		fmt::print("\n");

		// 422750754948214 is too low

		return count;
	};
}

day<data_t> day13 = day<data_t>(day_number, get_input, p1, p2);