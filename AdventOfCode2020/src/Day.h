#pragma once

#include <string>
#include "Utils.h"

#include <vector>
#include <iostream>
#include <fstream>

class Day
{
public:
	Day(const std::string& pathToInput1)
		:pathToInput1(pathToInput1), pathToInput2(pathToInput1)
	{

	}

	Day(const std::string& pathToInput1, const std::string& pathToInput2 )
		:pathToInput1(pathToInput1), pathToInput2(pathToInput2)
	{

	}

	virtual ~Day() = default;

	int getDayNumber() { return dayNumber; }

	//Defualt implementation for each part
	virtual std::string part1() { return ""; }
	virtual std::string part2() { return ""; }

protected:
	int dayNumber = 0;
	std::string pathToInput1;
	std::string pathToInput2;
};