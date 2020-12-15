#include "Day15.h"

#include <unordered_map>

std::string Day15::part1()
{
	auto inputStr = loadFileAsString(pathToInput1);

	std::vector<int> input;

	for (auto& number : split(inputStr, ","))
	{
		input.push_back(std::stoi(number));
	}

	struct Turns
	{
		int lastTurn = -1;
		int previousTurn = -1;
	};

	std::unordered_map<int, Turns> numbers;

	int lastNumber = input[input.size() - 1];

	for (int i = 0; i < input.size(); i++)
	{
		numbers[input[i]] = { i + 1, -1 };
	}

	for (int turn = input.size() + 1; turn <= 2020; turn++)
	{
		int previousTurn = numbers[lastNumber].previousTurn;
		int lastTurn = numbers[lastNumber].lastTurn;

		if (lastTurn == -1 || previousTurn == -1)
		{
			//Number not found, new number is 0
			lastNumber = 0;
		}
		else
		{
			lastNumber = lastTurn - previousTurn;
		}

		numbers[lastNumber].previousTurn = numbers[lastNumber].lastTurn;
		numbers[lastNumber].lastTurn = turn;
	}



	return std::to_string(lastNumber);
}

//INEFFICIENT IMPLEMENTATION!!
std::string Day15::part2()
{
	auto inputStr = loadFileAsString(pathToInput2);

	std::vector<int> input;

	for (auto& number : split(inputStr, ","))
	{
		input.push_back(std::stoi(number));
	}

	struct Turns
	{
		int lastTurn = -1;
		int previousTurn = -1;
	};

	std::unordered_map<int, Turns> numbers;

	int lastNumber = input[input.size() - 1];

	for (int i = 0; i < input.size(); i++)
	{
		numbers[input[i]] = { i + 1, -1 };
	}

	for (int turn = input.size() + 1; turn <= 30000000; turn++)
	{
		int previousTurn = numbers[lastNumber].previousTurn;
		int lastTurn = numbers[lastNumber].lastTurn;

		if (lastTurn == -1 || previousTurn == -1)
		{
			//Number not found, new number is 0
			lastNumber = 0;
		}
		else
		{
			lastNumber = lastTurn - previousTurn;
		}

		numbers[lastNumber].previousTurn = numbers[lastNumber].lastTurn;
		numbers[lastNumber].lastTurn = turn;
	}



	return std::to_string(lastNumber);
}
