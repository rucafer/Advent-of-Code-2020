#pragma once

#include "Day.h"

class Day5 : public Day
{
public:
	Day5(const std::string& path)
		:Day(path)
	{
		dayNumber = 5;
	}

	std::string part1() override;
	std::string part2() override;
private:
	const static int rowsNumber = 128;
	const static int columnNumber = 8;
	const static int numberRowChars = 7;
	const static int numberColChars = 3;
};