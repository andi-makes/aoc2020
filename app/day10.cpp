#include "registry.h"

namespace {
	using data_t			 = std::vector<int>;
	constexpr int day_number = 10;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		int buf;
		while (input >> buf) {
			data.push_back(buf);
		}
		data.push_back(0);
		std::sort(data.begin(), data.end());
		data.push_back(data.back() + 3);
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int diff_1 = 0;
		int diff_3 = 0;
		for (int i = 1; i < data.size(); ++i) {
			if (data[i] - data[i - 1] == 1) {
				diff_1++;
			} else if (data[i] - data[i - 1] == 3) {
				diff_3++;
			}
		}
		return diff_1 * diff_3;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		auto get_branches = [&data](int index) -> int {
			// int d0 = data[index];
			std::vector<int> distances;
			if (index >= 3) {
				distances.push_back(data[index] - data[index - 1]);
				distances.push_back(data[index] - data[index - 2]);
				distances.push_back(data[index] - data[index - 3]);
			} else if (index == 2) {
				distances.push_back(data[index] - data[index - 1]);
				distances.push_back(data[index] - data[index - 2]);
			} else if (index == 1) {
				distances.push_back(data[index] - data[index - 1]);
			} else {
				return 0;
			}

			int branches = 0;

			if (std::find(distances.begin(), distances.end(), 1) !=
				distances.end()) {
				++branches;
			}
			if (std::find(distances.begin(), distances.end(), 2) !=
				distances.end()) {
				++branches;
			}
			if (std::find(distances.begin(), distances.end(), 3) !=
				distances.end()) {
				++branches;
			}
			return branches;
		};
		std::vector<int64_t> b{ 1 };
		for (int i = 1; i < data.size(); ++i) {
			// std::cout << data[i] << ": " << get_branches(i) << std::endl;
			b.push_back(get_branches(i));
			// int branches = get_branches(i);
			if (b.back() == 2) {
				b[b.size() - 1] = b[b.size() - 2] + b[b.size() - 3];
			} else if (b.back() == 3) {
				b[b.size() - 1] =
					b[b.size() - 2] + b[b.size() - 3] + b[b.size() - 4];
			} else if (b.back() == 1) {
				b[b.size() - 1] = b[b.size() - 2];
			}
		}
		return b.back();
	};
}

auto day10 = day<data_t>(day_number, get_input, p1, p2);