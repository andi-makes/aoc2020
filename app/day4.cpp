#include "registry.h"

namespace {
	using data_t			 = std::vector<std::string>;
	constexpr int day_number = 4;

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

		void reset() {
			fields = 0;
			byr	   = "";
			iyr	   = "";
			eyr	   = "";
			hgt	   = "";
			hcl	   = "";
			ecl	   = "";
			pid	   = "";
			cid	   = "";
		}

		void print() {
			std::cout << "byr[" << byr << "],\t"
					  << "iyr[" << iyr << "],\t"
					  << "eyr[" << eyr << "],\t"
					  << "hgt[" << hgt << "],\t"
					  << "hcl[" << hcl << "],\t"
					  << "ecl[" << ecl << "],\t"
					  << "pid[" << pid << "],\t"
					  << "cid[" << cid << "]\n";
		}

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

	auto get_input = [](data_t& data) -> void {
		std::ifstream input{ "day" + std::to_string(day_number) + ".txt" };

		std::string buf;
		std::string block = "";
		while (std::getline(input, buf)) {
			if (buf == "") {
				data.push_back(block);
				block = "";
			} else {
				if (block != "") {
					block += " " + buf;
				} else {
					block += buf;
				}
			}
		}
	};

	auto p1 = [](const data_t& data) -> int64_t {
		std::regex r{ "(\\w{3}):([\\d#\\w]+)" };

		int valid = 0;

		Passport p;

		for (std::string block : data) {
			p.reset();
			std::sregex_iterator begin{ block.begin(), block.end(), r };
			std::sregex_iterator end = std::sregex_iterator();

			for (std::sregex_iterator i = begin; i != end; ++i) {
				std::smatch match = *i;
				// std::cout << match[1] << " -> " << match[2] << '\n';
				if (match[1].str() == ("byr")) {
					p.byr = (match[2].str());
					p.fields |= Passport::BYR;
				} else if (match[1].str() == ("iyr")) {
					p.iyr = (match[2].str());
					p.fields |= Passport::IYR;
				} else if (match[1].str() == ("eyr")) {
					p.eyr = (match[2].str());
					p.fields |= Passport::EYR;
				} else if (match[1].str() == ("hgt")) {
					p.hgt = (match[2].str());
					p.fields |= Passport::HGT;
				} else if (match[1].str() == ("hcl")) {
					p.hcl = (match[2].str());
					p.fields |= Passport::HCL;
				} else if (match[1].str() == ("ecl")) {
					p.ecl = (match[2].str());
					p.fields |= Passport::ECL;
				} else if (match[1].str() == ("pid")) {
					p.pid = (match[2].str());
					p.fields |= Passport::PID;
				} else if (match[1].str() == ("cid")) {
					p.cid = (match[2].str());
					p.fields |= Passport::CID;
				}
			}

			p.fields |= Passport::CID;

			if (p.fields == 0xFF) {
				++valid;
			}
		}
		return valid;
	};

	auto p2 = [](const data_t& data) -> int64_t {
		std::regex r{ "(\\w{3}):([\\d|#\\w]+)" };

		int valid = 0;

		Passport p;

		for (std::string block : data) {
			std::sregex_iterator begin{ block.begin(), block.end(), r };
			std::sregex_iterator end = std::sregex_iterator();
			p.reset();

			for (std::sregex_iterator i = begin; i != end; ++i) {
				std::smatch match = *i;
				// std::cout << match[1] << " -> " << match[2] << '\n';
				if (match[1].str() == ("byr")) {
					p.byr = (match[2].str());
					p.fields |= Passport::BYR;
				} else if (match[1].str() == ("iyr")) {
					p.iyr = (match[2].str());
					p.fields |= Passport::IYR;
				} else if (match[1].str() == ("eyr")) {
					p.eyr = (match[2].str());
					p.fields |= Passport::EYR;
				} else if (match[1].str() == ("hgt")) {
					p.hgt = (match[2].str());
					p.fields |= Passport::HGT;
				} else if (match[1].str() == ("hcl")) {
					p.hcl = (match[2].str());
					p.fields |= Passport::HCL;
				} else if (match[1].str() == ("ecl")) {
					p.ecl = (match[2].str());
					p.fields |= Passport::ECL;
				} else if (match[1].str() == ("pid")) {
					p.pid = (match[2].str());
					p.fields |= Passport::PID;
				} else if (match[1].str() == ("cid")) {
					p.cid = (match[2].str());
					p.fields |= Passport::CID;
				}
			}

			p.fields |= Passport::CID;

			if (p.fields == 0xFF) {
				std::regex r_year{ "(\\d{4})" };
				std::smatch match;
				if (std::regex_match(p.byr, match, r_year)) {
					int z = std::stoi(match[1].str());
					if (z < 1920 || z > 2002) {
						continue;
					}
				} else {
					continue;
				}
				if (std::regex_match(p.iyr, match, r_year)) {
					int z = std::stoi(match[1].str());
					if (z < 2010 || z > 2020) {
						continue;
					}
				} else {
					continue;
				}
				if (std::regex_match(p.eyr, match, r_year)) {
					int z = std::stoi(match[1].str());
					if (z < 2020 || z > 2030) {
						continue;
					}
				} else {
					continue;
				}

				std::regex r_hgt{ "(\\d+)(cm|in)" };
				if (std::regex_match(p.hgt, match, r_hgt)) {
					int z = std::stoi(match[1].str());
					if (match[2].str() == "cm") {
						if (z < 150 || z > 193) {
							continue;
						}
					} else if (match[2].str() == "in") {
						if (z < 59 || z > 76) {
							continue;
						}
					} else {
						continue;
					}
				} else {
					continue;
				}

				std::regex r_color{ "#[0-9a-f]{6}" };
				if (!std::regex_match(p.hcl, r_color)) {
					continue;
				}

				std::regex r_ecl{ "amb|blu|brn|gry|grn|hzl|oth" };
				if (!std::regex_match(p.ecl, r_ecl)) {
					continue;
				}

				std::regex r_pid{ "^\\d{9}$" };
				if (!std::regex_match(p.pid, r_pid)) {
					continue;
				}

				++valid;
			}
		}

		return valid;
	};
}

day<data_t> day4 = day<data_t>(day_number, get_input, p1, p2);