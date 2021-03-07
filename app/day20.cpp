#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 20;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	struct Chunk {
		std::vector<uint16_t> data;

		std::vector<uint16_t> edges;
		int matches;

		int id;

		void match(const Chunk& other) {
			int m = 0;
			for (auto e : other.edges) {
				if (std::find(edges.begin(), edges.end(), e) != edges.end()) {
					m++;
				}
			}
			matches = std::max(matches, m);
		}

		Chunk(const std::vector<std::string>& chunk, int id) :
			id(id), matches(0) {
			uint16_t left = 0, right = 0;
			for (int y = 0; y < chunk.size(); ++y) {
				uint16_t buf = 0;
				left |= chunk[y][0] << y;
				right |= chunk[y][chunk.size() - 1] << y;
				for (int x = 0; x < chunk[y].length(); ++x) {
					if (chunk[y][chunk[y].size() - 1 - x] == '#') {
						buf |= (1 << x);
					}
				}
				data.push_back(buf);
			}
			edges.push_back(data[0]);
			edges.push_back(data[data.size() - 1]);
			edges.push_back(left);
			edges.push_back(right);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		uint64_t count = 1;

		std::map<int, Chunk> chunks;

		std::vector<std::string> buffer;
		int id_buffer;
		std::regex r_tile{ "Tile (\\d+):" };
		for (auto line : data) {
			std::smatch m;
			if (std::regex_match(line, m, r_tile)) {
				id_buffer = std::stoi(m.str(1));
				buffer.clear();
			} else if (line == "") {
				chunks.insert({ id_buffer, { buffer, id_buffer } });
			} else {
				buffer.push_back(line);
			}
		}

		for (auto pair : chunks) {
			for (auto other : chunks) {
				if (other.first != pair.first) {
					pair.second.match(other.second);
				}
			}
			if (pair.second.matches == 2) {
				std::cout << pair.first << std::endl;
			}
		}

		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		int count = 0;
		for (auto line : data) {
		}
		return count;
	};
}

auto day20 = day<data_t>(day_number, get_input, p1, p2);