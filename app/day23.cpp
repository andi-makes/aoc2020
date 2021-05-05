#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 23;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	struct rb {
		rb* next;
		rb* prev;

		int value;

		rb(int value) : next(nullptr), prev(nullptr), value(value) {}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		uint64_t value = 962713854;
		int count	   = 0;

		std::array<rb*, 9> values;
		int highest = 0;
		int lowest	= 10;
		for (int i = values.size() - 1; i >= 0; --i) {
			values[i] = new rb(value % 10);
			if (value % 10 > highest) {
				highest = value % 10;
			}
			if (value % 10 < lowest) {
				lowest = value % 10;
			}
			value /= 10;
			if (i == 0) {
				values[i]->prev = values[values.size() - 1];
				values[i]->next = values[i + 1];
			} else if (i == values.size() - 1) {
				values[i]->prev = values[i - 1];
				values[i]->next = values[0];
			} else {
				values[i]->prev = values[i - 1];
				values[i]->next = values[i + 1];
			}
		}

		rb* current		= values[0];
		values[8]->next = current;	  // idk why
		auto print		= [&](rb* c) {
			 for (int i = 0; i < values.size(); ++i) {
				 fmt::print("{}, ", c->value);
				 c = c->next;
			 }
			 //  std::cout << std::endl;
			 fmt::print("\n");
		};

		for (int i = 0; i < 100; ++i) {
			rb* ending		 = current->next->next->next;
			rb* beginning	 = current->next;
			rb* insert_after = ending->next;
			auto destination = current->value - 1;

			current->next	   = ending->next;
			ending->next->prev = current;

			auto begin_value = current->next->value;
			auto counter	 = 0;
			while (insert_after->value != destination) {
				insert_after = insert_after->next;
				++counter;
				if (counter == 6) {
					destination--;
					if (destination < lowest) {
						destination = highest;
					}
				}
			}

			// fmt::print("{}", insert_after->value);

			rb* insert_before	= insert_after->next;
			insert_before->prev = ending;
			ending->next		= insert_before;

			insert_after->next = beginning;
			beginning->prev	   = insert_after;

			print(current);
			current = current->next;
		}

		fmt::print("\n");

		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto line : data) {
		}
		return count;
	};
}

day<data_t> day23 = day<data_t>(day_number, get_input, p1, p2);