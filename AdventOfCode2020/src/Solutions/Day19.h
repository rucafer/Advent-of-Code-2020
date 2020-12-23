#pragma once

#include "Day.h"

#include <unordered_map>

class Day19 : public Day
{
public:
	Day19(const std::string& path)
		:Day(path)
	{
		dayNumber = 19;
	}

	std::string part1() override;
	std::string part2() override;

private:
	int calculateLengths(int ruleNumber, std::unordered_map<int, std::string>& rules, std::unordered_map<int, int>& lenghts);
	bool match(const std::string& line, int ruleNumber, std::unordered_map<int, std::string>& rules, std::unordered_map<int, int>& lengths);
};