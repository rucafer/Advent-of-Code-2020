#pragma once

#include "Day.h"

class Day10 : public Day
{
public:
	Day10(const std::string& path)
		:Day(path)
	{
		dayNumber = 10;
	}

	std::string part1() override;
	std::string part2() override;
};