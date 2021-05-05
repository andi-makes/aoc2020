#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 2;

	auto get_input = [](data_t& data) -> void {
		using namespace std::literals::string_literals;
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		std::regex r{ "(\\d+)-(\\d+) ([a-z]): ([a-z]+)" };
		int valid = 0;

		for (auto line : data) {
			std::smatch m;
			if (std::regex_match(line, m, r)) {
				int number_of_c = 0;
				for (char c : m[4].str()) {
					if (c == m[3].str()[0]) {
						++number_of_c;
					}
				}
				if (number_of_c <= std::stoi(m[2].str()) &&
					number_of_c >= std::stoi(m[1].str())) {
					++valid;
				}
			}
		}

		return valid;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::regex r{ "(\\d+)-(\\d+) ([a-z]): ([a-z]+)" };
		int valid = 0;

		for (auto line : data) {
			std::smatch m;
			if (std::regex_match(line, m, r)) {
				std::string pwd = m[4].str();
				char c			= m[3].str()[0];
				int lower_pos	= std::stoi(m[1].str()) - 1;
				int upper_pos	= std::stoi(m[2].str()) - 1;

				if (pwd[lower_pos] != pwd[upper_pos] &&
					(pwd[lower_pos] == c || pwd[upper_pos] == c)) {
					++valid;
				}
			}
		}

		return valid;
	};
}

day<data_t> day2 = day<data_t>(day_number, get_input, p1, p2);