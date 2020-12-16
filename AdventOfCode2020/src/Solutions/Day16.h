#pragma once

#include "Day.h"

struct Range
{
	std::string name;
	int min0 = 0, max0 = 0;	//Second ragne
	int min1 = 0, max1 = 0;	//First range
};

class Day16 : public Day
{
public:
	Day16(const std::string& path)
		:Day(path)
	{
		dayNumber = 16;
	}

	std::string part1() override;
	std::string part2() override;

private:
	Range loadRange(const std::string& range);

	bool inRange(int number, const Range& range);
};