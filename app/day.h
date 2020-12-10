#pragma once

#include <chrono>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
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
		std::vector<std::string> time_prefixes{ "ns", "us", "ms", "s" };

		auto start = high_resolution_clock::now();
		get_input(data);
		auto end			  = high_resolution_clock::now();
		double duration_input = duration_cast<nanoseconds>(end - start).count();
		int index_input		  = 0;
		while (duration_input > 1000 && index_input < 2) {
			duration_input /= 1000;
			++index_input;
		}

		start			   = high_resolution_clock::now();
		auto result1	   = part1(data);
		end				   = high_resolution_clock::now();
		double duration_p1 = duration_cast<nanoseconds>(end - start).count();
		int index_p1	   = 0;
		while (duration_p1 > 1000 && index_p1 < 2) {
			duration_p1 /= 1000;
			++index_p1;
		}

		start			   = high_resolution_clock::now();
		auto result2	   = part2(data);
		end				   = high_resolution_clock::now();
		double duration_p2 = duration_cast<nanoseconds>(end - start).count();
		int index_p2	   = 0;
		while (duration_p2 > 1000 && index_p2 < 2) {
			duration_p2 /= 1000;
			++index_p2;
		}

		fmt::print("{0} [{1}{6}]\n{0}.1: [{2}|{3}{7}]\n{0}.2: [{4}|{5}{8}]\n",
				   number,
				   duration_input,
				   result1,
				   duration_p1,
				   result2,
				   duration_p2,
				   time_prefixes[index_input],
				   time_prefixes[index_p1],
				   time_prefixes[index_p2]);
	}

	day(int number,
		std::function<void(data_t&)> get_inp,
		std::function<int64_t(const data_t&)> p1,
		std::function<int64_t(const data_t&)> p2) :
		number(number),
		get_input(get_inp), part1(p1), part2(p2) {}
};
