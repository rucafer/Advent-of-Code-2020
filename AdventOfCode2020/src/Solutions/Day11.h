#pragma once

#include "Day.h"

class Day11 : public Day
{
public:
	Day11(const std::string& path)
		:Day(path)
	{
		dayNumber = 11;
	}

	std::string part1() override;
	std::string part2() override;
private:
	int countVisibleSeats(int row, int column, const std::vector<std::vector<char>>& table);
};