#pragma once

#include "Day.h"

class Day17 : public Day
{
public:
	Day17(const std::string& path)
		:Day(path)
	{
		dayNumber = 17;
	}

	std::string part1() override;
	std::string part2() override;

private:
	std::string getGridAsString(const std::vector<std::vector<std::vector<char>>>& grid, int indexOfStartingLayer);
	int findNumberOfNeighbors(const std::vector<std::vector<std::vector<char>>>& grid, int x, int y, int z);
	int findNumberOfNeighbors(const std::vector<std::vector<std::vector<std::vector<char>>>>& grid, int x, int y, int z, int w);
};