#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 19;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	struct Rule {
		int index;
		std::vector<int> other_rules;
		char c;
		bool end;

		std::string operator()(const std::map<int, Rule>& rules,
							   bool part2 = false) const {
			if (end) {
				return std::string{ c };
			}

			// static std::string ret = "";
			// if (ret != "") {
			// 	return ret;
			// }

			auto c = [&](int i) -> std::string { return rules.at(i)(rules); };

			if (part2) {
				if (index == 8) {
					return "((" + c(42) + ")+)";
				}
				if (index == 11) {
					std::string ret =
						"((" + c(42) + "){1}" + "(" + c(31) + "){1}";
					for (int i = 2; i < 8; ++i) {
						ret += "|(" + c(42) + "){" + std::to_string(i) + "}" +
							   "(" + c(31) + "){" + std::to_string(i) + "}";
					}
					return ret + ")";
				}
			}

			std::string ret = "(";
			for (auto i : other_rules) {
				if (i == -1) {
					ret += "|";
					continue;
				}
				ret += rules.at(i)(rules, part2);
			}
			return ret + ")";
		}

		Rule(int i, const std::string& other) : index(i), c(0), end(false) {
			std::stringstream s{ other };
			std::string buf;
			while (std::getline(s, buf, ' ')) {
				if (buf == "|") {
					other_rules.push_back(-1);
				} else {
					other_rules.push_back(std::stoi(buf));
				}
			}
		}
		Rule(int i, char c) : index(i), other_rules(), c(c), end(true) {}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		std::map<int, Rule> rules;

		std::regex r_rule{ R"((\d+): (.+))" };
		for (auto line : data) {
			if (line == "") {
				break;
			}
			std::smatch m;
			if (std::regex_match(line, m, r_rule)) {
				auto index	 = std::stoi(m.str(1));
				auto pattern = m.str(2);
				if (pattern[0] == '"') {
					rules.insert({ index, { index, pattern[1] } });
				} else {
					rules.insert({ index, { index, pattern } });
				}
			}
		}

		// for (auto pair : rules) {
		// 	fmt::print("{}: {}\n", pair.first, pair.second(rules));
		// }
		std::regex r_rule0{ rules.at(0)(rules) };
		int count = 0;
		for (auto line : data) {
			if (std::regex_match(line, r_rule0)) {
				++count;
			}
		}

		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::map<int, Rule> rules;

		std::regex r_rule{ R"((\d+): (.+))" };
		for (auto line : data) {
			if (line == "") {
				break;
			}
			std::smatch m;
			if (std::regex_match(line, m, r_rule)) {
				auto index	 = std::stoi(m.str(1));
				auto pattern = m.str(2);
				if (pattern[0] == '"') {
					rules.insert({ index, { index, pattern[1] } });
				} else {
					rules.insert({ index, { index, pattern } });
				}
			}
		}
		// rules[8]  = Rule{ "42 | 42 8" };
		// rules[11] = Rule{ "42 31 | 42 11 31" };
		rules.insert_or_assign(8, Rule{ 8, "42 | 42 8" });
		rules.insert_or_assign(11, Rule{ 11, "42 31 | 42 11 31" });

		// for (auto pair : rules) {
		// 	fmt::print("{}: {}\n", pair.first, pair.second(rules, true));
		// 	std::cout << std::flush;
		// }
		std::regex r_rule0{ rules.at(0)(rules, true) };
		int count = 0;
		for (auto line : data) {
			if (std::regex_match(line, r_rule0)) {
				++count;
				// std::cout << line << std::endl;
			}
		}
		// 337 too high
		// 336 too high

		return count;
	};
}

day<data_t> day19 = day<data_t>(day_number, get_input, p1, p2);