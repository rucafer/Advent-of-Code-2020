#pragma once

#include "Day.h"

class Day6 : public Day
{
public:
	Day6(const std::string& path)
		:Day(path)
	{
		dayNumber = 6;
	}

	std::string part1() override;
	std::string part2() override;
};