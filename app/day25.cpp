#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 25;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		uint64_t card_pub = 2069194;
		uint64_t door_pub = 16426071;
		int i_card		  = 0;
		int i_door		  = 0;

		int i		   = 0;
		uint64_t value = 1;
		while (i_card == 0 || i_door == 0) {
			value *= 7;
			value = value % uint64_t(20201227);

			if (value == card_pub) {
				std::cerr << "Found card_pub loop size: " << i << std::endl;
				i_card = i;
			} else if (value == door_pub) {
				std::cerr << "Found door_pub loop size: " << i << std::endl;

				i_door = i;
			}

			++i;
		}

		uint64_t ekey = 1;
		for (int i = 0; i <= i_card; ++i) {
			ekey *= door_pub;
			ekey = ekey % 20201227;
		}

		std::cout << ekey << std::endl;

		uint64_t ekey1 = 1;
		for (int i = 0; i <= i_door; ++i) {
			ekey1 *= card_pub;
			ekey1 = ekey1 % 20201227;
		}

		std::cout << ekey1 << std::endl;

		return ekey;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto line : data) {
		}
		return count;
	};
}

day<data_t> day25 = day<data_t>(day_number, get_input, p1, p2);