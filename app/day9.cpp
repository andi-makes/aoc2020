#include "registry.h"

namespace {
	using data_t			 = std::vector<int>;
	constexpr int day_number = 9;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		int buf;
		while (input >> buf) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		for (int start = 0, end = 25; end < data.size(); ++end, ++start) {
			int64_t goal = data[end];
			for (int i = start; i < end; ++i) {
				auto res = std::find(data.begin() + start,
									 data.begin() + start + end,
									 goal - data[i]);
				if (res != data.begin() + start + end) {
					if (*res != data[i]) {
						break;
					}
				}
				if (i == end - 1) {
					return goal;
				}
			}
		}
		return 0;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int solution_p1	  = 507622668;
		auto index_sol_p1 = 632;
		// int solution_p1 = 127;
		for (int64_t end = index_sol_p1; end > 0; --end) {
			int base = data[end];
			for (int64_t start = end - 1; start >= 0; --start) {
				base += data[start];
				if (base == solution_p1) {
					int min = solution_p1, max = 0;
					for (int i = start; i < end + 1; ++i) {
						if (data[i] < min) {
							min = data[i];
						}
						if (data[i] > max) {
							max = data[i];
						}
					}
					return min + max;
				}
				if (base > solution_p1) {
					break;
				}
			}
		}
		return 0;
	};
}

auto day9 = day<data_t>(day_number, get_input, p1, p2);