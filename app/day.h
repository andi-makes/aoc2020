#pragma once

#include <chrono>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

template<typename data_t>
struct day {
	data_t data;
	int number;
	std::function<void(data_t&)> get_input;

	std::function<int64_t(const data_t&)> part1;
	std::function<int64_t(const data_t&)> part2;

	void run() {
		using namespace std::chrono;
		auto start = high_resolution_clock::now();
		get_input(data);
		auto end			= high_resolution_clock::now();
		auto duration_input = duration_cast<microseconds>(end - start).count();

		start			 = high_resolution_clock::now();
		auto result1	 = part1(data);
		end				 = high_resolution_clock::now();
		auto duration_p1 = duration_cast<microseconds>(end - start).count();

		start			 = high_resolution_clock::now();
		auto result2	 = part2(data);
		end				 = high_resolution_clock::now();
		auto duration_p2 = duration_cast<microseconds>(end - start).count();

		fmt::print("{0} [{1}us]\n{0}.1: [{2}|{3}us]\n{0}.2: [{4}|{5}us]\n",
				   number,
				   duration_input,
				   result1,
				   duration_p1,
				   result2,
				   duration_p2);
	}

	day(int number,
		std::function<void(data_t&)> get_inp,
		std::function<int64_t(const data_t&)> p1,
		std::function<int64_t(const data_t&)> p2) :
		number(number),
		get_input(get_inp), part1(p1), part2(p2) {}
};
