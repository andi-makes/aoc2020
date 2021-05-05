#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 18;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int64_t count = 0;

		auto is_number = [](char c) -> bool { return c <= '9' && c >= '0'; };

		auto compute = [](std::string s) -> int64_t {
			std::stringstream in{ s };
			int64_t lhs;
			in >> lhs;
			int64_t rhs;
			char op;
			while (in >> op >> rhs) {
				if (op == '+') {
					lhs += rhs;
				} else if (op == '*') {
					lhs *= rhs;
				}
			}
			return lhs;
		};

		std::regex r_paren{ R"(\(([\d\s+*]+)\))" };

		for (auto line : data) {
			auto working_copy = line;

			std::smatch m;
			while (std::regex_search(working_copy, m, r_paren)) {
				std::string res = std::to_string(compute(m[1].str()));
				working_copy	= m.prefix().str();
				working_copy += res;
				working_copy += m.suffix().str();
			}
			// std::cout << line << ": ";
			// std::cout << compute(working_copy) << std::endl;
			count += compute(working_copy);
		}
		// 4294651785 too low
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int64_t count = 0;

		auto is_number = [](char c) -> bool { return c <= '9' && c >= '0'; };

		std::regex r_add{ R"((\d+) \+ (\d+))" };
		auto compute = [&](std::string s) -> int64_t {
			std::smatch m;
			while (std::regex_search(s, m, r_add)) {
				std::string res =
					std::to_string(std::stoll(m.str(1)) + std::stoll(m.str(2)));
				s = m.prefix();
				s += res;
				s += m.suffix();
			}

			std::stringstream in{ s };
			int64_t lhs;
			in >> lhs;
			int64_t rhs;
			char op;
			while (in >> op >> rhs) {
				if (op == '*') {
					lhs *= rhs;
				}
			}
			return lhs;
		};

		std::regex r_paren{ R"(\(([\d\s+*]+)\))" };

		for (auto line : data) {
			std::string working_copy = line;

			std::smatch m;
			while (std::regex_search(working_copy, m, r_paren)) {
				std::string match = std::to_string(compute(m[1].str()));

				working_copy = m.prefix().str();
				working_copy += match;
				working_copy += m.suffix().str();
			}

			// std::cout << line << ": ";
			// std::cout << compute(working_copy) << std::endl;
			count += compute(working_copy);
		}
		// 1653756970408 too low
		// 70476200484385 too low
		// 70722650566361
		return count;
	};
}

day<data_t> day18 = day<data_t>(day_number, get_input, p1, p2);