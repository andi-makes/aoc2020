#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 8;

	int e_ptr = 0;

	struct INSTRUCTION {
		int executed;

		std::string name;

		virtual void exec(int number) = 0;

		INSTRUCTION() : executed(0) {}
	};

	struct ACC : INSTRUCTION {
		static int accumulator;

		void exec(int number) {
			accumulator += number;
			++executed;
			++e_ptr;
		}
	};

	struct JMP : INSTRUCTION {
		void exec(int number) {
			e_ptr += number;
			++executed;
		}
	};

	struct NOP : INSTRUCTION {
		void exec(int number) {
			++executed;
			++e_ptr;
		}
	};

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		int count = 0;

		std::regex r{ "(\\w{3}) ([+-]\\d+)" };

		std::vector<std::pair<INSTRUCTION*, int>> code;
		int i = 0;
		for (auto line : data) {
			std::smatch m;
			if (std::regex_match(line, m, r)) {
				if (m[1].str() == "acc") {
					code.push_back({ new ACC(), std::stoi(m[2].str()) });
				} else if (m[1].str() == "jmp") {
					code.push_back({ new JMP(), std::stoi(m[2].str()) });
				} else if (m[1].str() == "nop") {
					code.push_back({ new NOP(), std::stoi(m[2].str()) });
				}
			}
		}

		while (code[e_ptr].first->executed == 0) {
			code[e_ptr].first->exec(code[e_ptr].second);
		}

		return ACC::accumulator;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;

		std::regex r{ "(\\w{3}) ([+-]\\d+)" };

		std::vector<std::pair<INSTRUCTION*, int>> code;
		std::vector<int> ptrs;
		int i = 0;
		for (int i = 0; i < data.size(); ++i) {
			std::smatch m;
			std::string line = data[i];
			if (std::regex_match(line, m, r)) {
				if (m[1].str() == "acc") {
					code.push_back({ new ACC(), std::stoi(m[2].str()) });
					code[code.size() - 1].first->name = "acc";
				} else if (m[1].str() == "jmp") {
					code.push_back({ new JMP(), std::stoi(m[2].str()) });
					code[code.size() - 1].first->name = "jmp";
					ptrs.push_back(i);
				} else if (m[1].str() == "nop") {
					code.push_back({ new NOP(), std::stoi(m[2].str()) });
					code[code.size() - 1].first->name = "nop";
					ptrs.push_back(i);
				}
			}
		}

		int prev_jmp = 0;

		auto execute = [&]() {
			e_ptr			 = 0;
			ACC::accumulator = 0;
			while (e_ptr != code.size() && code[e_ptr].first->executed == 0) {
				code[e_ptr].first->exec(code[e_ptr].second);
			}
			if (e_ptr == code.size()) {
				return true;
			} else {
				return false;
			}
		};

		auto backup = code;
		for (int i = 0; i < ptrs.size(); ++i) {
			code = backup;
			// auto instruct = code[ptrs[i]];
			if (code[ptrs[i]].first->name == "jmp") {
				code[ptrs[i]]			  = { new NOP(), code[ptrs[i]].second };
				code[ptrs[i]].first->name = "nop";
			} else if (code[ptrs[i]].first->name == "nop") {
				code[ptrs[i]]			  = { new JMP(), code[ptrs[i]].second };
				code[ptrs[i]].first->name = "jmp";
			}

			for (int j = 0; j < code.size(); ++j) {
				code[j].first->executed = 0;
			}

			if (execute()) {
				return ACC::accumulator;
			}
		}

		return 0;
	};
}
int ACC::accumulator = 0;

day<data_t> day8 = day<data_t>(day_number, get_input, p1, p2);