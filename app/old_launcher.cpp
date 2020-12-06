#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int day1_1() {
	std::ifstream input{ "day1.txt" };
	std::vector<int> day1;

	int buf = 0;
	while (input >> buf) {
		day1.push_back(buf);
	}

	for (int i = 0; i < 200; ++i) {
		for (int j = i + 1; j < 200; j++) {
			if (day1[i] + day1[j] == 2020) {
				// 436404
				return day1[i] * day1[j];
			}
		}
	}
	return -1;
}

int day1_2() {
	std::ifstream input{ "day1.txt" };
	std::vector<int> day1;

	int buf = 0;
	while (input >> buf) {
		day1.push_back(buf);
	}

	for (int i = 0; i < 200; ++i) {
		for (int j = i + 1; j < 200; j++) {
			int sum = day1[i] + day1[j];
			if (sum < 2020) {
				for (int k = j + 1; k < 200; ++k) {
					if (sum + day1[k] == 2020) {
						// 274879808
						return day1[i] * day1[j] * day1[k];
					}
				}
			}
		}
	}
	return -1;
}

int day2_1() {
	std::ifstream input{ "day2.txt" };
	int min, max;
	char character;
	char tmp;
	std::string pwd;

	std::vector<std::string> valid;
	int valid_count = 0;

	while (input >> min >> tmp >> max >> character >> tmp >> pwd) {
		// std::cout << min << " - " << max << " " << character << ": " << pwd
		// 		  << std::endl;
		int count = 0;
		for (char c : pwd) {
			if (c == character) {
				++count;
			}
		}
		if (count <= max && count >= min) {
			valid.push_back(pwd);
			++valid_count;
		}
	}
	return valid_count;
}

int day2_2() {
	std::ifstream input{ "day2.txt" };
	int min, max;
	char character;
	char tmp;
	std::string pwd;

	std::vector<std::string> valid;
	int valid_count = 0;

	while (input >> min >> tmp >> max >> character >> tmp >> pwd) {
		if (pwd.c_str()[min - 1] != pwd.c_str()[max - 1]) {
			if (pwd.c_str()[min - 1] == character ||
				pwd.c_str()[max - 1] == character) {
				valid_count++;
				// std::cout << pwd.c_str()[min - 1] << " " << min << " "
				// 		  << pwd.c_str()[max - 1] << " " << max << ": "
				// 		  << character << ": " << pwd << std::endl;
			}
		}
	}
	return valid_count;
}

int get_trees(const std::vector<std::string>& input, int incx, int incy) {
	int width = input[0].length();
	int index = 0;
	int trees = 0;
	for (int i = 0; i < input.size(); i += incy) {
		if (input[i][index % width] == '#') {
			++trees;
		}
		index += incx;
	}

	return trees;
}

int day3_1() {
	std::ifstream input{ "day3.txt" };

	std::vector<std::string> data;

	std::string line;
	while (std::getline(input, line)) {
		data.push_back(line);
	}

	int width = data[0].length();
	int index = 0;
	int trees = 0;
	for (auto l : data) {
		if (l[index % width] == '#') {
			++trees;
		}
		index += 3;
	}

	return trees;
}

int day3_2() {
	std::ifstream input{ "day3.txt" };

	std::vector<std::string> data;

	std::string line;
	while (std::getline(input, line)) {
		data.push_back(line);
	}

	return get_trees(data, 1, 1) * get_trees(data, 3, 1) *
		   get_trees(data, 5, 1) * get_trees(data, 7, 1) *
		   get_trees(data, 1, 2);
}

struct Passport {
	std::string byr;
	std::string iyr;
	std::string eyr;
	std::string hgt;
	std::string hcl;
	std::string ecl;
	std::string pid;
	std::string cid;

	uint8_t fields;

	Passport() : fields(0) {}
	static constexpr uint8_t BYR = 0b0000'0001;
	static constexpr uint8_t IYR = 0b0000'0010;
	static constexpr uint8_t EYR = 0b0000'0100;
	static constexpr uint8_t HGT = 0b0000'1000;
	static constexpr uint8_t HCL = 0b0001'0000;
	static constexpr uint8_t ECL = 0b0010'0000;
	static constexpr uint8_t PID = 0b0100'0000;
	static constexpr uint8_t CID = 0b1000'0000;
};

int day4_1() {
	std::ifstream input{ "day4.txt" };

	std::vector<Passport*> data;
	data.push_back(new Passport());

	std::regex r{ "(\\w{3}):([\\d|#\\w]+)" };

	std::string line;
	std::string block = "";
	int valid		  = 0;
	while (std::getline(input, line)) {
		if (line == "") {
			std::sregex_iterator begin{ block.begin(), block.end(), r };
			std::sregex_iterator end = std::sregex_iterator();

			for (std::sregex_iterator i = begin; i != end; ++i) {
				std::smatch match = *i;
				// std::cout << match[1] << " -> " << match[2] << '\n';
				if (match[1].str() == ("byr")) {
					data[data.size() - 1]->byr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::BYR;
				} else if (match[1].str() == ("iyr")) {
					data[data.size() - 1]->iyr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::IYR;
				} else if (match[1].str() == ("eyr")) {
					data[data.size() - 1]->eyr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::EYR;
				} else if (match[1].str() == ("hgt")) {
					data[data.size() - 1]->hgt = (match[2].str());
					data[data.size() - 1]->fields |= Passport::HGT;
				} else if (match[1].str() == ("hcl")) {
					data[data.size() - 1]->hcl = (match[2].str());
					data[data.size() - 1]->fields |= Passport::HCL;
				} else if (match[1].str() == ("ecl")) {
					data[data.size() - 1]->ecl = (match[2].str());
					data[data.size() - 1]->fields |= Passport::ECL;
				} else if (match[1].str() == ("pid")) {
					data[data.size() - 1]->pid = (match[2].str());
					data[data.size() - 1]->fields |= Passport::PID;
				} else if (match[1].str() == ("cid")) {
					data[data.size() - 1]->cid = (match[2].str());
					data[data.size() - 1]->fields |= Passport::CID;
				}
			}

			data[data.size() - 1]->fields |= Passport::CID;

			if (data[data.size() - 1]->fields == 0xFF) {
				++valid;
			}
			data.push_back(new Passport());
			block = "";
		} else {
			block += line + ' ';
		}
	}

	return valid;
	// 225 too low

	// Part 2: 162 to high
}

int day4_2() {
	std::ifstream input{ "day4.txt" };

	std::vector<Passport*> data;
	data.push_back(new Passport());

	std::regex r{ "(\\w{3}):([\\d|#\\w]+)" };

	std::string line;
	std::string block = "";
	int valid		  = 0;
	while (std::getline(input, line)) {
		if (line == "") {
			std::sregex_iterator begin{ block.begin(), block.end(), r };
			std::sregex_iterator end = std::sregex_iterator();

			for (std::sregex_iterator i = begin; i != end; ++i) {
				std::smatch match = *i;
				// std::cout << match[1] << " -> " << match[2] << '\n';
				if (match[1].str() == ("byr")) {
					try {
						int z = std::stoi(match[2].str());
						if (z < 1920 || z > 2002) {
							continue;
						}
					} catch (std::invalid_argument e) {
						continue;
					}

					data[data.size() - 1]->byr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::BYR;
				} else if (match[1].str() == ("iyr")) {
					try {
						int z = std::stoi(match[2].str());
						if (z < 2010 || z > 2020) {
							continue;
						}
					} catch (std::invalid_argument e) {
						continue;
					}
					data[data.size() - 1]->iyr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::IYR;
				} else if (match[1].str() == ("eyr")) {
					try {
						int z = std::stoi(match[2].str());
						if (z < 2020 || z > 2030) {
							continue;
						}
					} catch (std::invalid_argument e) {
						continue;
					}
					data[data.size() - 1]->eyr = (match[2].str());
					data[data.size() - 1]->fields |= Passport::EYR;
				} else if (match[1].str() == ("hgt")) {
					std::regex hgt_rgx{ "(\\d+)(cm|in)" };
					if (std::regex_search(match[2].str(), hgt_rgx)) {
						std::string height = match[2].str();
						std::sregex_iterator hgt_it{ height.begin(),
													 height.end(),
													 hgt_rgx };
						if (hgt_it != std::sregex_iterator()) {
							std::smatch hgt_match = *hgt_it;

							try {
								int z = std::stoi(hgt_match[1].str());
								if (hgt_match[2].str() == "cm") {
									if (z < 150 || z > 193) {
										continue;
									}
								} else if (hgt_match[2].str() == "in") {
									if (z < 59 || z > 76) {
										continue;
									}
								}
							} catch (std::invalid_argument e) {
								continue;
							}
						} else {
							continue;
						}
					} else {
						continue;
					}

					data[data.size() - 1]->hgt = (match[2].str());
					data[data.size() - 1]->fields |= Passport::HGT;
				} else if (match[1].str() == ("hcl")) {
					std::regex hgt_rgx{ "#[0-9a-f]{6}" };

					if (!std::regex_search(match[2].str(), hgt_rgx)) {
						continue;
					}

					// std::sregex_iterator hgt_it{ match[2].str().begin(),
					// 							 match[2].str().end(),
					// 							 hgt_rgx };
					// if (hgt_it == std::sregex_iterator()) {
					// 	continue;
					// }
					data[data.size() - 1]->hcl = (match[2].str());
					data[data.size() - 1]->fields |= Passport::HCL;
				} else if (match[1].str() == ("ecl")) {
					// amb blu brn gry grn hzl oth
					if (match[2].str() == "amb" || match[2].str() == "blu" ||
						match[2].str() == "brn" || match[2].str() == "gry" ||
						match[2].str() == "grn" || match[2].str() == "hzl" ||
						match[2].str() == "oth") {
						data[data.size() - 1]->ecl = (match[2].str());
						data[data.size() - 1]->fields |= Passport::ECL;
					}
				} else if (match[1].str() == ("pid")) {
					std::regex hgt_rgx{ "^\\d{9}$",
										std::regex_constants::ECMAScript };
					if (!std::regex_search(match[2].str(), hgt_rgx)) {
						continue;
					}

					data[data.size() - 1]->pid = (match[2].str());
					data[data.size() - 1]->fields |= Passport::PID;
				} else if (match[1].str() == ("cid")) {
					data[data.size() - 1]->cid = (match[2].str());
					data[data.size() - 1]->fields |= Passport::CID;
				}
			}

			data[data.size() - 1]->fields |= Passport::CID;

			if (data[data.size() - 1]->fields == 0xFF) {
				++valid;
			}
			data.push_back(new Passport());
			block = "";
		} else {
			block += line + ' ';
		}
	}

	for (auto p : data) {
		if (p->fields == 0xFF) {
			std::cout << "byr:" << p->byr << "\tiyr:" << p->iyr
					  << "\teyr:" << p->eyr << "\thgt:" << p->hgt
					  << "\thcl:" << p->hcl << "\tecl:" << p->ecl
					  << "\tpid:" << p->pid << '\n';
		}
	}

	return valid;
	// Part 2: 162 to high
}

uint32_t day5_1() {
	std::ifstream input{ "day5.txt" };

	std::vector<uint32_t> passport_data;

	std::string line;
	uint16_t highest = 0;
	while (std::getline(input, line)) {
		uint32_t buffer = 0;
		for (int i = 0; i < line.length(); ++i) {
			char c = line[line.length() - 1 - i];
			if (c == 'B' || c == 'R') {
				buffer |= (1 << i);
			}
		}

		std::replace(line.begin(), line.end(), 'F', '0');
		std::replace(line.begin(), line.end(), 'B', '1');

		std::replace(line.begin(), line.end(), 'L', '0');
		std::replace(line.begin(), line.end(), 'R', '1');

		if (buffer > highest) {
			highest = buffer;
		}

		passport_data.push_back(buffer);
	}
	return highest;
}

uint32_t day5_2() {
	std::ifstream input{ "day5.txt" };

	std::vector<uint32_t> passport_data;

	std::string line;
	uint16_t highest = 0;

	while (std::getline(input, line)) {
		uint32_t buffer = 0;
		for (int i = 0; i < line.length(); ++i) {
			char c = line[line.length() - 1 - i];
			if (c == 'B' || c == 'R') {
				buffer |= (1 << i);
			}
		}

		std::replace(line.begin(), line.end(), 'F', '0');
		std::replace(line.begin(), line.end(), 'B', '1');

		std::replace(line.begin(), line.end(), 'L', '0');
		std::replace(line.begin(), line.end(), 'R', '1');

		if (buffer > highest) {
			highest = buffer;
		}

		passport_data.push_back(buffer);
	}

	std::sort(passport_data.begin(), passport_data.end());

	for (int i = 0; i < passport_data.size(); ++i) {
		if (passport_data[i] + 1 != passport_data[i + 1]) {
			return passport_data[i] + 1;
		}
	}

	return 0;	 // 195 too low;
}

int day6_1() {
	std::ifstream input{ "day6.txt" };

	std::string line;
	int count = 0;
	std::map<char, bool> q;
	while (std::getline(input, line)) {
		if (line == "") {
			//
			count += q.size();

			q.clear();
		} else {
			for (char c : line) {
				q[c] = true;
			}
		}
	}
	return count;
}

int day6_2() {
	std::ifstream input{ "day6.txt" };

	std::string line;
	int line_count = 0;
	int count	   = 0;
	std::map<char, int> q;
	while (std::getline(input, line)) {
		if (line == "") {
			//
			for (auto pair : q) {
				if (pair.second == line_count) {
					count++;
				}
			}

			line_count = 0;
			q.clear();
		} else {
			for (char c : line) {
				q[c] += 1;
			}
			line_count++;
		}
	}
	return count;
}

int main() {
	std::cout << "Yeah, who am I kidding. I didn't program a launcher "
				 "beforehand. \nHere, watch this cat video instead: "
				 "https://cutt.ly/nhkFOYo"	  // Sorry, but this is a bad cat
											  // vid. I literally took the first
											  // video from youtube.
			  << std::endl;

	auto start	= std::chrono::high_resolution_clock::now();
	auto result = day6_2();
	auto end	= std::chrono::high_resolution_clock::now();

	std::cout << "Result: " << result << "\nTime: "
			  << std::chrono::duration_cast<std::chrono::microseconds>(end -
																	   start)
					 .count()
			  << " us" << std::endl;

	return 0;
}