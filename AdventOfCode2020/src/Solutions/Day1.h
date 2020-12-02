#pragma once

#include "Day.h"

class Day1 : public Day
{
public:
	Day1(const std::string& path)
	:Day(path)
	{
		dayNumber = 1; 
	}

	std::string part1() override;
	std::string part2() override;
};