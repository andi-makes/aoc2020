#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 16;

	struct ranges_t {
		int lower1, higher1;
		int lower2, higher2;
	};

	enum class SECTIONS { RULES, TICKET, OTHER };

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int count = 0;
		std::unordered_map<std::string, ranges_t> rules;

		std::vector<std::vector<std::pair<int, std::vector<std::string>>>>
			valid;
		SECTIONS region = SECTIONS::RULES;
		for (auto buf : data) {
			if (buf == "") continue;
			if (buf == "your ticket:") {
				region = SECTIONS::TICKET;
				continue;
			} else if (buf == "nearby tickets:") {
				region = SECTIONS::OTHER;
				continue;
			}
			switch (region) {
			case SECTIONS::RULES: {
				std::regex r_rules{ R"(([\w ]+): (\d+)-(\d+) or (\d+)-(\d+))" };
				std::smatch m;
				if (std::regex_match(buf, m, r_rules)) {
					rules.insert({ m[1],
								   { std::stoi(m[2]),
									 std::stoi(m[3]),
									 std::stoi(m[4]),
									 std::stoi(m[5]) } });
				}
			} break;
			case SECTIONS::TICKET: {
			} break;
			case SECTIONS::OTHER: {
				std::regex r_ticket{ R"((\d+),?)" };
				auto begin =
					std::sregex_iterator{ buf.begin(), buf.end(), r_ticket };
				auto end = std::sregex_iterator{};

				std::vector<std::pair<int, std::vector<std::string>>> line;
				bool invalid = false;
				for (auto it = begin; it != end; ++it) {
					std::smatch m = *it;

					auto input = std::stoi(m[1]);

					auto check_input = [](int in, ranges_t r) -> bool {
						return (in <= r.higher1 && in >= r.lower1) ||
							   (in <= r.higher2 && in >= r.lower2);
					};
					line.push_back({ input, {} });
					for (auto rule : rules) {
						if (check_input(input, rule.second)) {
							line[line.size() - 1].second.push_back(rule.first);
						}
					}

					if (line[line.size() - 1].second.size() == 0) {
						// Invalid number
						count += input;
						invalid = true;
					}
				}
				if (!invalid) {
					valid.push_back(line);
				}
			} break;
			}
		}
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int64_t count = 0;
		std::unordered_map<std::string, ranges_t> rules;

		std::vector<std::vector<std::pair<int, std::set<std::string>>>> valid;

		std::vector<std::pair<int, std::string>> myticket;
		SECTIONS region = SECTIONS::RULES;
		for (auto buf : data) {
			if (buf == "") continue;
			if (buf == "your ticket:") {
				region = SECTIONS::TICKET;
				continue;
			} else if (buf == "nearby tickets:") {
				region = SECTIONS::OTHER;
				continue;
			}
			switch (region) {
			case SECTIONS::RULES: {
				std::regex r_rules{ R"(([\w ]+): (\d+)-(\d+) or (\d+)-(\d+))" };
				std::smatch m;
				if (std::regex_match(buf, m, r_rules)) {
					rules.insert({ m[1],
								   { std::stoi(m[2]),
									 std::stoi(m[3]),
									 std::stoi(m[4]),
									 std::stoi(m[5]) } });
				}
			} break;
			case SECTIONS::TICKET: {
				std::regex r_ticket{ R"((\d+),?)" };
				auto begin =
					std::sregex_iterator{ buf.begin(), buf.end(), r_ticket };
				auto end = std::sregex_iterator{};

				std::vector<std::pair<int, std::vector<std::string>>> line;
				bool invalid = false;
				for (auto it = begin; it != end; ++it) {
					std::smatch m = *it;

					auto input = std::stoi(m[1]);
					myticket.push_back({ input, "" });
				}
			} break;
			case SECTIONS::OTHER: {
				std::regex r_ticket{ R"((\d+),?)" };
				auto begin =
					std::sregex_iterator{ buf.begin(), buf.end(), r_ticket };
				auto end = std::sregex_iterator{};

				std::vector<std::pair<int, std::set<std::string>>> line;
				bool invalid = false;
				int i		 = 0;
				for (auto it = begin; it != end; ++it, ++i) {
					std::smatch m = *it;

					auto input = std::stoi(m[1]);

					auto check_input = [](int in, ranges_t r) -> bool {
						return (in <= r.higher1 && in >= r.lower1) ||
							   (in <= r.higher2 && in >= r.lower2);
					};
					line.push_back({ input, {} });
					for (auto rule : rules) {
						if (check_input(input, rule.second)) {
							line[line.size() - 1].second.insert(rule.first);
						}
					}

					if (line[line.size() - 1].second.size() == 0) {
						// Invalid number
						count += input;
						invalid = true;
					}
				}
				if (!invalid) {
					valid.push_back(line);
				}
			} break;
			}
		}

		// Part 2 begin

		int found = 0;
		int cols  = valid[0].size();

		std::map<int, std::set<std::string>> columns;
		for (int x = 0; x < valid[0].size(); ++x) {
			for (auto rule : rules) {
				bool applies = true;
				for (int y = 0; y < valid.size(); ++y) {
					if (!valid[y][x].second.contains(rule.first)) {
						applies = false;
						break;
					}
				}
				if (applies) {
					columns[x].insert(rule.first);
				}
			}
		}
		while (found != cols) {
			for (int i = 0; i < valid[0].size(); ++i) {
				if (columns[i].size() == 1) {
					if (rules.contains(*columns[i].begin())) {
						rules.erase(*columns[i].begin());
						auto buffer = *columns[i].begin();
						// columns.clear();
						// columns[i].insert(buffer);
						for (auto& pair : columns) {
							pair.second.erase(buffer);
						}
						columns[i].insert(buffer);
						myticket[i].second = buffer;
						++found;
					}
				}
			}
		}

		// for (auto pair : columns) {
		// 	std::cout << pair.first << ": ";
		// 	for (auto name : pair.second) {
		// 		std::cout << name << ", ";
		// 	}
		// 	std::cout << std::endl;
		// }

		count = 1;
		for (int i = 0; i < myticket.size(); ++i) {
			std::regex r{ R"(departure)" };
			// std::cout << i << ": " << myticket[i].first << std::endl;
			if (std::regex_search(myticket[i].second, r)) {
				count *= myticket[i].first;
			}
		}
		return count;
	};
}

day<data_t> day16 = day<data_t>(day_number, get_input, p1, p2);