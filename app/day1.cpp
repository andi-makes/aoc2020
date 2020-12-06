#include "registry.h"

namespace {
	using data_t = std::vector<int>;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day1.txt" };

		int buf = 0;
		while (input >> buf) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		for (int i = 0; i < 200; ++i) {
			for (int j = i + 1; j < 200; j++) {
				if (data[i] + data[j] == 2020) {
					// 436404
					return data[i] * data[j];
				}
			}
		}
		return -1;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		for (int i = 0; i < 200; ++i) {
			for (int j = i + 1; j < 200; j++) {
				int sum = data[i] + data[j];
				if (sum < 2020) {
					for (int k = j + 1; k < 200; ++k) {
						if (sum + data[k] == 2020) {
							// 274879808
							return data[i] * data[j] * data[k];
						}
					}
				}
			}
		}
		return -1;
	};
}

auto day1 = day<std::vector<int>>(1, get_input, p1, p2);