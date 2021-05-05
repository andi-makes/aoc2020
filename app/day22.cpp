#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 22;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		std::vector<uint32_t> p1;
		std::vector<uint32_t> p2;

		int count	 = 0;
		bool player1 = false;
		for (auto line : data) {
			if (line[0] == 'P') {
				player1 = !player1;
			} else if (line != "") {
				if (player1) {
					p1.push_back(std::stol(line));
				} else {
					p2.push_back(std::stol(line));
				}
			}
		}

		while (p1.size() && p2.size()) {
			if (p1[0] > p2[0]) {
				p1.push_back(p1[0]);
				p1.push_back(p2[0]);
				p1.erase(p1.begin());
				p2.erase(p2.begin());
			} else if (p2[0] > p1[0]) {
				p2.push_back(p2[0]);
				p2.push_back(p1[0]);
				p1.erase(p1.begin());
				p2.erase(p2.begin());
			}
		}
		if (p1.size()) {
			for (int i = 0; i < p1.size(); ++i) {
				count += p1[i] * (p1.size() - i);
			}
		} else {
			for (int i = 0; i < p2.size(); ++i) {
				count += p2[i] * (p2.size() - i);
			}
		}

		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::vector<uint32_t> p1;
		std::vector<uint32_t> p2;

		int count	 = 0;
		bool player1 = false;
		for (auto line : data) {
			if (line[0] == 'P') {
				player1 = !player1;
			} else if (line != "") {
				if (player1) {
					p1.push_back(std::stol(line));
				} else {
					p2.push_back(std::stol(line));
				}
			}
		}

		auto recurse_combat = [](std::vector<uint32_t> pl1,
								 std::vector<uint32_t> pl2)
			-> std::pair<std::pair<uint32_t, uint32_t>, bool> {
			auto playing_card1 = pl1[0];
			auto playing_card2 = pl2[0];

			pl1.erase(pl1.begin());
			pl2.erase(pl2.begin());

			if (playing_card1 > pl1.size() && playing_card2 > pl2.size()) {
			} else {
				if (playing_card1 > playing_card2) {
				}
			}
		};

		while (p1.size() && p2.size()) {
		}
		if (p1.size()) {
			for (int i = 0; i < p1.size(); ++i) {
				count += p1[i] * (p1.size() - i);
			}
		} else {
			for (int i = 0; i < p2.size(); ++i) {
				count += p2[i] * (p2.size() - i);
			}
		}

		return count;
	};
}

day<data_t> day22 = day<data_t>(day_number, get_input, p1, p2);