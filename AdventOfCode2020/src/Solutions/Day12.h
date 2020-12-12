#pragma once

#include "Day.h"

class Day12 : public Day
{
public:
	Day12(const std::string& path)
		:Day(path)
	{
		dayNumber = 12;
	}

	std::string part1() override;
	std::string part2() override;
};