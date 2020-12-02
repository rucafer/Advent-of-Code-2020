#pragma once

#include "Day.h"

class Day1 : public Day
{
public:
	Day1(const std::string& pathToPart1, const std::string& pathToPart2)
	:Day(pathToPart1, pathToPart1)
	{
		dayNumber = 1; 
	}

	std::string part1() override;
	std::string part2() override;
};