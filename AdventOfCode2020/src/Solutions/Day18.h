#pragma once

#include "Day.h"

class Day18 : public Day
{
public:
	Day18(const std::string& path)
		:Day(path)
	{
		dayNumber = 18;
	}

	std::string part1() override;
	std::string part2() override;

private:
	long long solve(std::string expression);
	long long solve2(std::string expression);
};