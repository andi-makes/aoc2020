#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 5;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		uint16_t highest = 0;
		for (auto line : data) {
			uint16_t buffer = 0;
			for (int i = 0; i < line.length(); ++i) {
				char c = line[line.length() - 1 - i];
				if (c == 'B' || c == 'R') {
					buffer |= (1 << i);
				}
			}

			if (buffer > highest) {
				highest = buffer;
			}
		}

		return highest;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		uint16_t highest = 0;
		std::vector<uint16_t> passport_data;

		for (auto line : data) {
			uint16_t buffer = 0;
			for (int i = 0; i < line.length(); ++i) {
				char c = line[line.length() - 1 - i];
				if (c == 'B' || c == 'R') {
					buffer |= (1 << i);
				}
			}

			if (buffer > highest) {
				highest = buffer;
			}

			passport_data.push_back(buffer);
		}

		std::sort(passport_data.begin(), passport_data.end());

		for (int i = 0; i < passport_data.size(); ++i) {
			if (passport_data[i] + 1 != passport_data[i + 1]) {
				return passport_data[i] + 1;
			}
		}

		return -1;
	};
}

auto day5 = day<data_t>(day_number, get_input, p1, p2);