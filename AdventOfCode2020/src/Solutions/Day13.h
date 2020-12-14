#pragma once

#include "Day.h"

class Day13 : public Day
{
public:
	Day13(const std::string& path)
		:Day(path)
	{
		dayNumber = 13;
	}

	std::string part1() override;
	std::string part2() override;

private:
	long long findxi(long long N, int ni);
};