#include "registry.h"

namespace {
	using data_t			 = std::vector<std::pair<int, int>>;
	constexpr int day_number = 15;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		int buf;
		int i = 1;
		while (input >> buf) {
			data.push_back({ buf, i });
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		// std::vector<int> v{ 0, 3, 6 };
		std::vector<int> v{ 11, 18, 0, 20, 1, 7, 16 };
		// fmt::print("0,\n3,\n6,\n");
		while (v.size() != 2020) {
			auto last_spoken_number = v.back();
			int distance			= 0;
			for (int i = 1; i < v.size(); ++i) {
				if (v[v.size() - 1 - i] == last_spoken_number) {
					distance = i;
					break;
				}
			}
			// fmt::print("{},\n", distance);
			v.push_back(distance);
		}
		return v.back();
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::unordered_map<int, int> m{ { 11, 1 }, { 18, 2 }, { 0, 3 },
										{ 20, 4 }, { 1, 5 },  { 7, 6 },
										{ 16, 7 } };

		int last_spoken_number = 16;
		int vsize			   = 7;
		while (vsize != 30000000) {
			int distance = 0;
			if (m.contains(last_spoken_number)) {
				auto m_index = m[last_spoken_number];
				m.insert_or_assign(last_spoken_number, vsize);
				distance = vsize - m_index;
			} else {
				m.insert_or_assign(last_spoken_number, vsize);
			}
			last_spoken_number = (distance);
			++vsize;
		}
		return last_spoken_number;
	};
}

day<data_t> day15 = day<data_t>(day_number, get_input, p1, p2);