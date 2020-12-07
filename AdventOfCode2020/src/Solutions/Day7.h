#pragma once

#include "Day.h"

#include <map>

class Day7 : public Day
{
public:
	Day7(const std::string& path)
		:Day(path)
	{
		dayNumber = 7;
	}

	std::string part1() override;
	std::string part2() override;

private:
	struct Bag
	{
		std::string name;
		int count;
	};

	int addBagsRecursive(const std::string& name, std::map<std::string, std::vector<Bag>>& map);
};