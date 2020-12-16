#include "registry.h"

#include <fmt/color.h>

int main(int argc, char** argv) {
	fmt::print(fmt::fg(fmt::terminal_color::blue), "  ~");
	fmt::print(fmt::fg(fmt::terminal_color::cyan), "~");
	fmt::print(fmt::fg(fmt::terminal_color::green), "  Advent of Code 2020  ");
	fmt::print(fmt::fg(fmt::terminal_color::cyan), "~");
	fmt::print(fmt::fg(fmt::terminal_color::blue), "~\n");

	fmt::print(fmt::fg(fmt::terminal_color::red), " ~");
	fmt::print(fmt::fg(fmt::terminal_color::magenta), "~");
	fmt::print(fmt::fg(fmt::terminal_color::yellow),
			   " Solutions by andi_makes ");
	fmt::print(fmt::fg(fmt::terminal_color::magenta), "~");
	fmt::print(fmt::fg(fmt::terminal_color::red), "~\n\n");

	if (argc != 1) {
		std::cout << "Direct run Mode." << std::endl;
		// day1.run();
		// day2.run();
		// day3.run();
		// day4.run();
		// day5.run();
		// day6.run();
		// day7.run();
		// day8.run();
		// day9.run();
		// day10.run();
		// day11.run();
		// day12.run();
		// day13.run();
		// day14.run();
		// day15.run();
		day16.run();
		// day17.run();
		// day18.run();
		// day19.run();
		// day20.run();
		// day21.run();
		// day22.run();
		// day23.run();
		// day24.run();
		// day25.run();
		return 0;
	}

	fmt::print(fmt::fg(fmt::color::medium_sea_green),
			   "REPL mode. Please enter a command.\n");
	fmt::print(fmt::fg(fmt::color::indian_red),
			   "  * exit, quit ... exit the program\n");
	fmt::print(fmt::fg(fmt::color::indian_red),
			   "  * day[1-25]  ... execute the given day ★☆◯\n");

	std::string line;
	while (true) {
		fmt::print(fmt::fg(fmt::color::chocolate) | fmt::emphasis::bold, ">: ");

		std::getline(std::cin, line);

		if (line == "exit" || line == "quit") {
			break;
		}

		std::regex r_cat{ R"((?:cat|gadse|katze|kitty)(?:video|vid)?)" };
		if (std::regex_search(line, r_cat)) {
			std::cout << "So you want a cat video? Fine. Here you go:\n"
					  << "https://cutt.ly/nhkFOYo"	  // Still a bad cat video.
					  << std::endl;
			continue;
		}

		std::regex r_day{ "day(\\d+)" };
		std::smatch m;
		if (std::regex_match(line, m, r_day)) {
			int i = std::stoi(m[1]);

			switch (i) {
			case 1: day1.run(); break;
			case 2: day2.run(); break;
			case 3: day3.run(); break;
			case 4: day4.run(); break;
			case 5: day5.run(); break;
			case 6: day6.run(); break;
			case 7: day7.run(); break;
			case 8: day8.run(); break;
			case 9: day9.run(); break;
			case 10: day10.run(); break;
			case 11: day11.run(); break;
			case 12: day12.run(); break;
			case 13: day13.run(); break;
			case 14: day14.run(); break;
			case 15: day15.run(); break;
			case 16: day16.run(); break;
			case 17: day17.run(); break;
			case 18: day18.run(); break;
			case 19: day19.run(); break;
			case 20: day20.run(); break;
			case 21: day21.run(); break;
			case 22: day22.run(); break;
			case 23: day23.run(); break;
			case 24: day24.run(); break;
			case 25: day25.run(); break;
			default:
				std::cout << "Please enter a valid day! (day[1-25])"
						  << std::endl;
			}
			continue;
		}
		std::cout << "Enter a valid command!" << std::endl;
	}

	return 0;
}