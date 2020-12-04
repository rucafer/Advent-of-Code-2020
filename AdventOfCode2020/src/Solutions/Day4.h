#pragma once

#include "Day.h"

class Day4 : public Day
{
public:
	Day4(const std::string& path)
		:Day(path)
	{
		dayNumber = 4;
	}

	std::string part1() override;
	std::string part2() override;
private:
	bool isFieldValid(const std::string& field);
private:
	std::vector<std::string> compulsoryFields{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	std::vector<std::string> optionalFields{ "cid" };
};