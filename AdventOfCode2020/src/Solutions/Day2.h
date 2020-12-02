#pragma once

#include "Day.h"

class Day2 : public Day
{
public:
	Day2(const std::string& path)
		:Day(path)
	{
		dayNumber = 2;
	}

	std::string part1() override;
	std::string part2() override;
};