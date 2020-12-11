#include "Day10.h"

#include <unordered_map>
#include <algorithm>

std::string Day10::part1()
{
	std::vector<int> input = loadFileAsIntList(pathToInput1);
	std::sort(input.begin(), input.end());

	int count1 = 0, count3 = 0;

	int previousValue = 0;	//Seat adapter

	for (int value : input)
	{
		int diff = value - previousValue;

		if (diff == 1)
		{
			count1++;
		}
		else if (diff == 3)
		{
			count3++;
		}

		if (diff > 3)
		{
			return "Error";
		}

		previousValue = value;
	}

	//Add 1 to count of elements with difference 3 (last adapter)
	count3++;

	return std::to_string(count1 * count3);
}

std::string Day10::part2()
{
	std::vector<int> input = loadFileAsIntList(pathToInput1);
	input.push_back(0);
	std::sort(input.rbegin(), input.rend());

	std::unordered_map<int, long long> optionsPerAdapter;

	optionsPerAdapter[input[0] + 3] = 1;

	for (int i : input)
	{
		//The number of options of an adapter is the sum of the options of each compatible adapter
		optionsPerAdapter[i] = optionsPerAdapter[i + 1] + optionsPerAdapter[i + 2] + optionsPerAdapter[i + 3];
	}

	return std::to_string(optionsPerAdapter[input[input.size() - 1]]);
}
