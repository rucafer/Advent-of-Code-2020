#pragma once

#include "Day.h"

class Day9 : public Day
{
public:
	Day9(const std::string& path)
		:Day(path)
	{
		dayNumber = 9;
	}

	std::string part1() override;
	std::string part2() override;
};