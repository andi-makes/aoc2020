#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 14;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		uint64_t count = 0;
		std::regex r_mask{ "mask = (\\w+)$" };
		std::regex r_mem{ "mem\\[(\\d+)\\] = (\\d+)$" };
		uint64_t and_mask = 0;
		uint64_t or_mask  = 0;
		std::map<uint64_t, uint64_t> mem;
		for (auto line : data) {
			std::smatch m;
			if (std::regex_match(line, m, r_mask)) {
				std::string new_mask = m[1].str();
				and_mask			 = 0;
				or_mask				 = 0;
				for (int i = 0; i < new_mask.length(); ++i) {
					char c = new_mask[new_mask.length() - 1 - i];
					if (c == '0') {
						and_mask |= (1ull << i);
					} else if (c == '1') {
						or_mask |= (1ull << i);
					}
				}
			} else if (std::regex_match(line, m, r_mem)) {
				mem.insert_or_assign(
					std::stoull(m[1].str()),
					std::stoull(m[2].str()) & uint64_t(~and_mask) | (or_mask));
			}
		}

		for (auto set : mem) {
			count += set.second;
		}
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		uint64_t count = 0;
		std::regex r_mask{ "mask = (\\w+)$" };
		std::regex r_mem{ "mem\\[(\\d+)\\] = (\\d+)$" };
		uint64_t mask  = 0;
		uint64_t xmask = 0;
		std::vector<uint64_t> xmask_index;
		std::map<uint64_t, uint64_t> mem;
		for (auto line : data) {
			std::smatch m;

			if (std::regex_match(line, m, r_mask)) {
				std::string new_mask = m[1].str();
				mask				 = 0;
				xmask				 = 0;
				xmask_index.clear();
				for (int i = 0; i < new_mask.length(); ++i) {
					char c = new_mask[new_mask.length() - 1 - i];
					if (c == 'X') {
						xmask_index.push_back(i);
						xmask |= (1ull << i);
					} else if (c == '1') {
						mask |= (1ull << i);
					}
				}
				// std::cout << "Mask Xs: " << xmask_index.size() << std::endl;
			} else if (std::regex_match(line, m, r_mem)) {
				// std::cout << line << std::endl;
				uint64_t adr = std::stoull(m[1].str());
				uint64_t val = std::stoull(m[2].str());
				adr &= ~xmask;
				adr |= mask;

				std::vector<uint64_t> adrs;
				adrs.push_back(adr);
				for (auto index : xmask_index) {
					auto l = adrs.size();
					for (auto i = 0; i < l; ++i) {
						adrs.push_back(adrs[i] | (1ull << index));
					}
				}
				// std::cout << " " << adrs.size() << std::endl;

				for (auto a : adrs) {
					// std::cout << "  mem[" << a << "] = " << val << std::endl;
					mem.insert_or_assign(a, val);
				}
			}
		}

		for (auto set : mem) {
			count += set.second;
		}
		// too low: 1476254159004
		//          698679167277
		//          810026586880
		// correct: 2308180581795
		return count;
	};
}

auto day14 = day<data_t>(day_number, get_input, p1, p2);