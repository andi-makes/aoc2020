#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 7;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	struct Bag {
		std::string name;
		std::vector<std::string> parents;
		std::map<std::string, int> children;
	};

	auto p1 = [](const data_t& data) -> int64_t {
		std::regex r{
			R"((\w+ \w+) bags contain ((?:\d+ \w+ \w+ bags?,? ?)*)\.)"
		};
		std::regex r2{ "(\\d+) (\\w+ \\w+) bags?" };

		std::map<std::string, Bag*> lookup;

		int64_t count = 0;
		for (auto line : data) {
			std::smatch m1;
			if (std::regex_match(line, m1, r)) {
				std::sregex_iterator begin{ line.begin(), line.end(), r2 };
				std::sregex_iterator end;
				for (auto it = begin; it != end; ++it) {
					std::smatch m2 = *it;

					std::string parent_name = m1[1];

					std::string child_name = m2[2];
					int child_count		   = std::stoi(m2[1]);

					if (lookup.find(parent_name) != lookup.end()) {
						lookup[parent_name]->children.insert(
							{ child_name, child_count });
					} else {
						lookup[parent_name] = new Bag{
							parent_name, {}, { { child_name, child_count } }
						};
					}

					if (lookup.find(child_name) != lookup.end()) {
						lookup[child_name]->parents.push_back(parent_name);
					} else {
						lookup[child_name] =
							new Bag{ child_name, { parent_name }, {} };
					}
				}
			}
		}

		std::vector<std::string> already_processed;

		std::function<int64_t(std::string)> recursive =
			[&](std::string name) -> int64_t {
			int64_t c = 0;
			for (auto p : lookup[name]->parents) {
				if (std::find(already_processed.begin(),
							  already_processed.end(),
							  p) == already_processed.end()) {
					// if not already processed
					++c;
				}
			}

			for (auto p : lookup[name]->parents) {
				if (std::find(already_processed.begin(),
							  already_processed.end(),
							  p) == already_processed.end()) {
					c += recursive(p);
					already_processed.push_back(p);
				}
			}
			already_processed.push_back(name);

			return c;
		};
		count = recursive("shiny gold");

		return count;	 // 510 too high, 336 too low, 337 it is
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::regex r{
			R"((\w+ \w+) bags contain ((?:\d+ \w+ \w+ bags?,? ?)*)\.)"
		};
		std::regex r2{ "(\\d+) (\\w+ \\w+) bags?" };

		std::map<std::string, Bag*> lookup;

		int64_t count = 0;
		for (auto line : data) {
			std::smatch m1;
			if (std::regex_match(line, m1, r)) {
				std::sregex_iterator begin{ line.begin(), line.end(), r2 };
				std::sregex_iterator end;
				for (auto it = begin; it != end; ++it) {
					std::smatch m2 = *it;

					std::string parent_name = m1[1];

					std::string child_name = m2[2];
					int child_count		   = std::stoi(m2[1]);

					if (lookup.find(parent_name) != lookup.end()) {
						lookup[parent_name]->children.insert(
							{ child_name, child_count });
					} else {
						lookup[parent_name] = new Bag{
							parent_name, {}, { { child_name, child_count } }
						};
					}

					if (lookup.find(child_name) != lookup.end()) {
						lookup[child_name]->parents.push_back(parent_name);
					} else {
						lookup[child_name] =
							new Bag{ child_name, { parent_name }, {} };
					}
				}
			}
		}

		std::function<int64_t(std::string)> recursive =
			[&](std::string name) -> int64_t {
			int64_t c = 0;

			for (auto child : lookup[name]->children) {
				c += (recursive(child.first) + 1) * child.second;
			}

			return c;
		};
		count = recursive("shiny gold");

		return count;	 // 44172 too low, 50100 it is!
	};
}

day<data_t> day7 = day<data_t>(day_number, get_input, p1, p2);