#pragma once

#include "Day.h"

class Day3 : public Day
{
public:
	Day3(const std::string& path)
		:Day(path)
	{
		dayNumber = 3;
	}

	std::string part1() override;
	std::string part2() override;

private:
	int getTreeCount(const std::vector<std::string>& input, int slopeRight, int slopeDown);
	std::string debuggingOutput;
};
