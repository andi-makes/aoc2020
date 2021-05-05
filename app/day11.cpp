#include "registry.h"

namespace {
	using data_t			 = std::vector<char>;
	constexpr int day_number = 11;

	int width = 0, height = 0;

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		while (std::getline(input, buf)) {
			width = buf.length();
			for (char c : buf) {
				data.push_back(c);
				// std::cout << c;
			}
			++height;
			// std::cout << std::endl;
		}
		// std::cout << std::endl;
	};

	auto p1 = [](const data_t& data) -> int64_t {
		auto copy = data;
		auto edit = data;

		auto get_neighbours = [&](int index) -> int {
			int c = 0;
			if (index % width == 0) {
				// We are at the left edge (for glory)
				if (index / width == 0) {
					// We are on the top-left
					if (copy[index + 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index + width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index + width + 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				} else if (index / width == height - 1) {
					// We are at the bottom-left
					if (copy[index + 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index - width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index - width + 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				} else {
					if (copy[index + 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index + width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index + width + 1] == '#') {
						c++;	// ok, it gets old now
					}
					if (copy[index - width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index - width + 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				}

			} else if (index % width == width - 1) {
				// We are at the right edge
				if (index / width == 0) {
					// We are on the top-right
					if (copy[index - 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index + width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index + width - 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				} else if (index / width == height - 1) {
					// We are at the bottom-right
					if (copy[index - 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index - width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index - width - 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				} else {
					if (copy[index - 1] == '#') {
						c++;	// Get it?
					}
					if (copy[index + width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index + width - 1] == '#') {
						c++;	// ok, it gets old now
					}
					if (copy[index - width] == '#') {
						c++;	// Come on, that joke isn't even that bad
					}
					if (copy[index - width - 1] == '#') {
						c++;	// ok, it gets old now
					}
					return c;
				}
			}

			if (index / width == 0) {
				// We are on the top
				if (copy[index - 1] == '#') {
					c++;	// Get it?
				}
				if (copy[index + 1] == '#') {
					c++;	// Come on, that joke isn't even that bad
				}
				if (copy[index + width] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index + width + 1] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index + width - 1] == '#') {
					c++;	// ok, it gets old now
				}
				return c;
			} else if (index / width == height - 1) {
				// We are at the bottom
				if (copy[index - 1] == '#') {
					c++;	// Get it?
				}
				if (copy[index + 1] == '#') {
					c++;	// Come on, that joke isn't even that bad
				}
				if (copy[index - width] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index - width + 1] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index - width - 1] == '#') {
					c++;	// ok, it gets old now
				}
				return c;
			} else {
				// Somewhere in the middle
				if (copy[index - 1] == '#') {
					c++;	// Get it?
				}
				if (copy[index + 1] == '#') {
					c++;	// Come on, that joke isn't even that bad
				}
				if (copy[index - width] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index - width + 1] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index - width - 1] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index + width] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index + width + 1] == '#') {
					c++;	// ok, it gets old now
				}
				if (copy[index + width - 1] == '#') {
					c++;	// ok, it gets old now
				}
				return c;
			}
		};

		int changed = 1;
		while (changed != 0) {
			for (int i = 0, w = 0; i < copy.size(); ++i) {
				if (copy[i] != '.') {
					if (get_neighbours(i) == 0) {
						edit[i] = '#';
					} else if (get_neighbours(i) >= 4) {
						edit[i] = 'L';
					}
				}
			}
			changed = 0;
			for (int i = 0; i < copy.size(); ++i) {
				if (copy[i] != edit[i]) {
					changed = 1;
					break;
				}
			}
			copy = edit;
		}
		int used = 0;
		for (char c : copy) {
			if (c == '#') {
				used++;
			}
		}
		return used;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::vector<std::vector<char>> map;
		for (int y = 0; y < height; ++y) {
			std::vector<char> tmp;
			for (int x = 0; x < width; ++x) {
				tmp.push_back(data[x + y * width]);
			}
			map.push_back(tmp);
		}

		auto print_map = [&]() {
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					std::cout << map[y][x];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		};

		auto get_neighbours = [&](int y_, int x_) {
			// Right
			int full = 0;
			for (int x = x_ + 1; x < width; ++x) {
				if (map[y_][x] == '#') {
					full++;
					break;
				} else if (map[y_][x] == 'L') {
					break;
				}
			}

			// Left
			for (int x = x_ - 1; x >= 0; --x) {
				if (map[y_][x] == '#') {
					full++;
					break;
				} else if (map[y_][x] == 'L') {
					break;
				}
			}

			// Up
			for (int y = y_ - 1; y >= 0; --y) {
				if (map[y][x_] == '#') {
					full++;
					break;
				} else if (map[y][x_] == 'L') {
					break;
				}
			}

			// Down
			for (int y = y_ + 1; y < height; ++y) {
				if (map[y][x_] == '#') {
					full++;
					break;
				} else if (map[y][x_] == 'L') {
					break;
				}
			}

			// Up right
			for (int x = x_ + 1, y = y_ - 1; x < width && y >= 0; ++x, --y) {
				if (map[y][x] == '#') {
					full++;
					y = -1;
					break;
				} else if (map[y][x] == 'L') {
					y = -1;
					break;
				}
			}

			// Down right
			for (int x = x_ + 1, y = y_ + 1; x < width && y < height;
				 ++x, ++y) {
				if (map[y][x] == '#') {
					full++;
					y = height;
					break;
				} else if (map[y][x] == 'L') {
					y = height;
					break;
				}
			}

			// Up left
			for (int x = x_ - 1, y = y_ - 1; x >= 0 && y >= 0; --x, --y) {
				if (map[y][x] == '#') {
					full++;

					break;
				} else if (map[y][x] == 'L') {
					break;
				}
			}

			// Down left
			for (int x = x_ - 1, y = y_ + 1; x >= 0 && y < height; --x, ++y) {
				if (map[y][x] == '#') {
					full++;
					break;
				} else if (map[y][x] == 'L') {
					break;
				}
			}
			return full;
		};

		int changed = 1;

		std::vector<std::vector<char>> map_copy = map;
		while (changed != 0) {
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					if (map_copy[y][x] == '.') continue;
					int neighbours = get_neighbours(y, x);
					if (neighbours == 0) {
						map_copy[y][x] = '#';
					} else if (neighbours >= 5) {
						map_copy[y][x] = 'L';
					}
				}
			}
			changed = 0;
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					if (map[y][x] != map_copy[y][x]) {
						changed = 1;

						y = height;
						break;
					}
				}
			}
			map = map_copy;
		}
		int used = 0;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (map_copy[y][x] == '#') {
					used++;
				}
			}
		}
		return used;
	};
}

day<data_t> day11 = day<data_t>(day_number, get_input, p1, p2);