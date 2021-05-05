#include "registry.h"

struct Position3D {
	int32_t x, y, z;

	bool operator==(const Position3D& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	Position3D operator+(const Position3D& other) {
		Position3D ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		ret.z = z + other.z;
		return ret;
	}

	Position3D(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
	Position3D() : x(0), y(0), z(0) {}
};

struct Position4D {
	int32_t x, y, z, w;

	bool operator==(const Position4D& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z) &&
			   (w == other.w);
	}

	Position4D operator+(const Position4D& other) {
		Position4D ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		ret.z = z + other.z;
		ret.w = w + other.w;
		return ret;
	}

	Position4D(int32_t x, int32_t y, int32_t z, int32_t w) :
		x(x), y(y), z(z), w(w) {}
	Position4D() : x(0), y(0), z(0), w(0) {}
};

namespace std {
	template<>
	struct hash<Position3D> {
		std::size_t operator()(const Position3D& p) const {
			return std::hash<int32_t>()(p.x) ^
				   (std::hash<int32_t>()(p.y) << 1) ^
				   (std::hash<int32_t>()(p.z) << 2);
		}
	};

	template<>
	struct hash<Position4D> {
		std::size_t operator()(const Position4D& p) const {
			return std::hash<int32_t>()(p.x) ^
				   (std::hash<int32_t>()(p.y) << 1) ^
				   (std::hash<int32_t>()(p.z) << 2) ^
				   (std::hash<int32_t>()(p.w) << 3);
		}
	};
}

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 17;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			data.push_back(buf);
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		using map_t = std::unordered_map<Position3D, bool>;
		using pos_t = Position3D;
		map_t map;

		// Parse input
		int32_t minx = 0, maxx = data[0].size(), miny = 0, maxy = data.size(),
				minz = 0, maxz = 1;
		for (int y = 0; y < data.size(); ++y) {
			for (int x = 0; x < data[y].size(); ++x) {
				map[{ x, y, 0 }] = data[y][x] == '#';
			}
		}

		auto check_cell = [](pos_t pos, map_t map) -> int {
			int neighbours = 0;

			for (auto z = 1; z >= -1; --z) {
				for (int y = 1; y >= -1; --y) {
					for (int x = -1; x <= 1; ++x) {
						if (z == 0 && y == 0 && x == 0) {
							continue;
						}

						if (map[pos + pos_t{ x, y, z }]) {
							++neighbours;
						}
					}
				}
			}
			return neighbours;
		};

		// for (int i = 0; i < 6; i++) {
		auto working_copy = map;

		for (int i = 0; i < 6; ++i) {
			minz -= 1;
			maxz += 1;

			miny -= 1;
			maxy += 1;

			minx -= 1;
			maxx += 1;

			for (int z = minz; z < maxz; ++z) {
				for (int y = miny; y < maxy; ++y) {
					for (int x = minx; x < maxx; x++) {
						// std::cout << check_cell({ x, y, z }, map);
						pos_t pos		= { x, y, z };
						auto neighbours = check_cell(pos, map);
						if (map[pos] && !(neighbours == 2 || neighbours == 3)) {
							working_copy[pos] = false;
						} else if (!map[pos] && neighbours == 3) {
							working_copy[pos] = true;
						}
					}
					// std::cout << std::endl;
				}
				// std::cout << std::endl;
			}
			map = working_copy;
		}
		// }

		int count = 0;
		for (auto pair : map) {
			if (pair.second) {
				++count;
			}
		}
		return count;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		using pos_t = Position4D;
		using map_t = std::unordered_map<pos_t, bool>;
		map_t map;

		// Parse input
		int32_t minx = 0, maxx = data[0].size(), miny = 0, maxy = data.size(),
				minz = 0, maxz = 1, minw = 0, maxw = 1;
		for (int y = 0; y < data.size(); ++y) {
			for (int x = 0; x < data[y].size(); ++x) {
				map[{ x, y, 0, 0 }] = data[y][x] == '#';
			}
		}

		auto check_cell = [](pos_t pos, map_t map) -> int {
			int neighbours = 0;

			for (auto w = 1; w >= -1; --w) {
				for (auto z = 1; z >= -1; --z) {
					for (int y = 1; y >= -1; --y) {
						for (int x = -1; x <= 1; ++x) {
							if (z == 0 && y == 0 && x == 0 && w == 0) {
								continue;
							}

							if (map[pos + pos_t{ x, y, z, w }]) {
								++neighbours;
							}
						}
					}
				}
			}
			return neighbours;
		};

		// for (int i = 0; i < 6; i++) {
		auto working_copy = map;

		for (int i = 0; i < 6; ++i) {
			minz -= 1;
			maxz += 1;

			miny -= 1;
			maxy += 1;

			minx -= 1;
			maxx += 1;

			minw -= 1;
			maxw += 1;

			for (int w = minw; w < maxw; ++w) {
				for (int z = minz; z < maxz; ++z) {
					for (int y = miny; y < maxy; ++y) {
						for (int x = minx; x < maxx; x++) {
							// std::cout << check_cell({ x, y, z }, map);
							pos_t pos		= { x, y, z, w };
							auto neighbours = check_cell(pos, map);
							if (map[pos] &&
								!(neighbours == 2 || neighbours == 3)) {
								working_copy[pos] = false;
							} else if (!map[pos] && neighbours == 3) {
								working_copy[pos] = true;
							}
						}
						// std::cout << std::endl;
					}
					// std::cout << std::endl;
				}
			}
			map = working_copy;
		}
		// }

		int count = 0;
		for (auto pair : map) {
			if (pair.second) {
				++count;
			}
		}
		return count;
	};
}

day<data_t> day17 = day<data_t>(day_number, get_input, p1, p2);