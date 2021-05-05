#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 6;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int count = 0;
		std::map<char, bool> q;
		for (auto line : data) {
			if (line == "") {
				//
				count += q.size();

				q.clear();
			} else {
				for (char c : line) {
					q[c] = true;
				}
			}
		}
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count	   = 0;
		int line_count = 0;
		std::map<char, int> q;
		for (auto line : data) {
			if (line == "") {
				//
				for (auto pair : q) {
					if (pair.second == line_count) {
						count++;
					}
				}

				line_count = 0;
				q.clear();
			} else {
				for (char c : line) {
					q[c] += 1;
				}
				line_count++;
			}
		}
		return count;
	};
}

day<data_t> day6 = day<data_t>(day_number, get_input, p1, p2);