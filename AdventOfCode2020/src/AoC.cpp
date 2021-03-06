#include "Day.h"
#include "Utils.h"

//Example:
//#include "../Examples/Solutions/Day0.h"

#include "Solutions/Day1.h"
#include "Solutions/Day2.h"
#include "Solutions/Day3.h"
#include "Solutions/Day4.h"
#include "Solutions/Day5.h"
#include "Solutions/Day6.h"
#include "Solutions/Day7.h"
#include "Solutions/Day8.h"
#include "Solutions/Day9.h"
#include "Solutions/Day10.h"
#include "Solutions/Day11.h"
#include "Solutions/Day12.h"
#include "Solutions/Day13.h"
#include "Solutions/Day14.h"
#include "Solutions/Day15.h"
#include "Solutions/Day16.h"
#include "Solutions/Day17.h"
#include "Solutions/Day18.h"
#include "Solutions/Day19.h"

#include <vector>
#include <chrono>


static std::vector<Day*> daysList;


static void AddDays()
{
	daysList.push_back(new Day1("./Files/Day1_1.txt"));
	daysList.push_back(new Day2("./Files/Day2_1.txt"));
	daysList.push_back(new Day3("./Files/Day3_1.txt"));
	daysList.push_back(new Day4("./Files/Day4_1.txt"));
	daysList.push_back(new Day5("./Files/Day5_1.txt"));
	daysList.push_back(new Day6("./Files/Day6_1.txt"));
	daysList.push_back(new Day7("./Files/Day7_1.txt"));
	daysList.push_back(new Day8("./Files/Day8_1.txt"));
	daysList.push_back(new Day9("./Files/Day9_1.txt"));
	daysList.push_back(new Day10("./Files/Day10_1.txt"));
	daysList.push_back(new Day11("./Files/Day11_1.txt"));
	daysList.push_back(new Day12("./Files/Day12_1.txt"));
	daysList.push_back(new Day13("./Files/Day13_1.txt"));
	daysList.push_back(new Day14("./Files/Day14_1.txt"));
	daysList.push_back(new Day15("./Files/Day15_1.txt"));
	daysList.push_back(new Day16("./Files/Day16_1.txt"));
	daysList.push_back(new Day17("./Files/Day17_1.txt"));
	daysList.push_back(new Day18("./Files/Day18_1.txt"));
	daysList.push_back(new Day19("./Files/Day19_1.txt"));
}

static void runDay(Day* day)
{
	std::cout << getDayHeader(day->getDayNumber()) << std::endl;

	//Part 1
	std::cout << PART_ONE_HEADER << std::endl;
	print_yellow();
	std::cout << "Output: ";
	print_default();
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << day->part1();
	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "\t elapsed time: " << duration / 1000.0f << " s" << std::endl;

	if (writeDebuggingInfo && day->getPart1DebuggingInfo() != "")
	{
		std::cout << "DEBUGGING INFO:" << std::endl;
		std::cout << day->getPart1DebuggingInfo() << std::endl;
	}

	//Part 2
	std::cout << PART_TWO_HEADER << std::endl;
	print_yellow();
	std::cout << "Output: ";
	print_default();
	t1 = std::chrono::high_resolution_clock::now();
	std::cout << day->part2();
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "\t elapsed time: " << duration / 1000.0f << " s" << std::endl;

	if (writeDebuggingInfo && day->getPart2DebuggingInfo() != "")
	{
		std::cout << "DEBUGGING INFO:" << std::endl;
		std::cout << day->getPart2DebuggingInfo() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	AddDays();

	bool runOnlyLast = false;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-l") == 0)
		{
			runOnlyLast = true;
		}
		else if(strcmp(argv[i], "-d") == 0)
		{
			writeDebuggingInfo = true;
		}
	}

	if (runOnlyLast)
	{
		runDay(daysList[daysList.size() - 1]);
	}
	else
	{
		for (Day* day : daysList)
		{
			runDay(day);
		}
	}
}