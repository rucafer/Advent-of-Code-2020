#pragma once

#include "Day.h"

class Day14 : public Day
{
public:
	Day14(const std::string& path)
		:Day(path)
	{
		dayNumber = 14;
	}

	std::string part1() override;
	std::string part2() override;

private:
	void addToMemory(std::vector<std::string>& indices, std::vector<uint64_t>& values, const std::string& newIndex, uint64_t newValue);
	//True if newIndex includes numbers form oldIndex
	bool intersect(const std::string& oldIndex, const std::string& newIndex);

	std::string intToBinaryString(uint64_t number);
};