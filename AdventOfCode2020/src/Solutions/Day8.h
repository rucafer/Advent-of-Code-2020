#pragma once

#include "Day.h"

class Day8 : public Day
{
public:
	Day8(const std::string& path)
		:Day(path)
	{
		dayNumber = 8;
	}

	std::string part1() override;
	std::string part2() override;

private:
	bool runProgram(std::vector<std::string> &program, int& acc);
};