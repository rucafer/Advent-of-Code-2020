#pragma once

#include "Day.h"

class Day2 : public Day
{
public:
	Day2(const std::string& pathToPart1, const std::string& pathToPart2)
		:Day(pathToPart1, pathToPart1)
	{
		dayNumber = 2;
	}

	std::string part1() override;
	std::string part2() override;
};