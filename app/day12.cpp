#include "registry.h"

namespace {
	using data_t			 = std::vector<std::pair<char, int>>;
	constexpr int day_number = 12;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		char c;
		int i;
		while (input >> c >> i) {
			// std::cout << c << ", " << i << std::endl;
			data.push_back({ c, i });
		}
	};

	struct Vector {
		int x = 0, y = 0;
	};

	auto p1 = [](const data_t& data) -> int64_t {
		Vector pos;
		char facing[] = "NESW";
		int offset	  = 1;
		for (auto set : data) {
			// fmt::print("pos: [{}|{}], Instruction: {}, {}, Facing {}\n",
			// 		   pos.x,
			// 		   pos.y,
			// 		   set.first,
			// 		   set.second,
			// 		   facing[offset]);
			// std::cin.get();
			switch (set.first) {
			case 'N': pos.y += set.second; break;
			case 'S': pos.y -= set.second; break;
			case 'E': pos.x += set.second; break;
			case 'W': pos.x -= set.second; break;
			case 'L':
				offset -= set.second / 90;
				if (offset < 0) {
					offset += 4;
				}
				break;
			case 'R':
				offset += set.second / 90;
				offset = offset % 4;
				break;
			case 'F':
				switch (facing[offset]) {
				case 'N': pos.y += set.second; break;
				case 'S': pos.y -= set.second; break;
				case 'W': pos.x -= set.second; break;
				case 'E': pos.x += set.second; break;
				}
				break;
			}
		}
		// 1587 too high
		return std::abs(pos.x) + std::abs(pos.y);
	};

	auto p2 = [](const data_t& data) -> int64_t {
		Vector pos;
		Vector waypoint{ 10, 1 };
		char facing[] = "NESW";
		int offset	  = 1;
		for (auto set : data) {
			// fmt::print("pos: [{}|{}], Instruction: {}, {}, Facing [{}|{}]\n",
			// 		   pos.x,
			// 		   pos.y,
			// 		   set.first,
			// 		   set.second,
			// 		   waypoint.x,
			// 		   waypoint.y);
			// std::cin.get();
			switch (set.first) {
			case 'N': waypoint.y += set.second; break;
			case 'S': waypoint.y -= set.second; break;
			case 'E': waypoint.x += set.second; break;
			case 'W': waypoint.x -= set.second; break;
			case 'L': {
				Vector buf = waypoint;
				switch (set.second) {
				case 270:
					waypoint.y = buf.x;
					waypoint.x = -buf.y;
					buf		   = waypoint;
				case 180:
					waypoint.y = buf.x;
					waypoint.x = -buf.y;
					buf		   = waypoint;
				case 90: waypoint.y = buf.x; waypoint.x = -buf.y;
				}
			} break;
			case 'R': {
				Vector buf = waypoint;
				switch (set.second) {
				case 270:
					waypoint.y = -buf.x;
					waypoint.x = buf.y;
					buf		   = waypoint;
				case 180:
					waypoint.y = -buf.x;
					waypoint.x = buf.y;
					buf		   = waypoint;
				case 90: waypoint.y = -buf.x; waypoint.x = buf.y;
				}
			} break;
			case 'F':
				pos.x += waypoint.x * set.second;
				pos.y += waypoint.y * set.second;
				break;
			}
		}
		return std::abs(pos.x) + std::abs(pos.y);
	};
}

day<data_t> day12 = day<data_t>(day_number, get_input, p1, p2);