#include "Day5.h"

std::string Day5::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int maxId = 0;

	for (auto& str : input)
	{
		int row = 0, col = 0;

		int min = 0, max = rowsNumber;

		for (int i = 0; i < numberRowChars; i++)
		{
			int midPoint = min + (max - min + 1) / 2;
			if (str[i] == 'F')
			{
				max = midPoint - 1;
			}
			else
			{
				min = midPoint;
			}
		}

		row = min;	//Or row = max, both are the same

		min = 0; max = columnNumber;

		for (int i = numberRowChars; i < numberRowChars + numberColChars; i++)
		{
			int midPoint = min + (max - min + 1) / 2;
			if (str[i] == 'L')
			{
				max = midPoint - 1;
			}
			else
			{
				min = midPoint;
			}
		}

		col = min;	//Or col = max, both are the same

		int id = row * 8 + col;

		if (id > maxId)
		{
			maxId = id;
		}
	}

	return std::to_string(maxId);
}

std::string Day5::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int maxId = 0;
	std::vector<int> seatIds;
	int output = 0;

	for (auto& str : input)
	{
		int row = 0, col = 0;

		int min = 0, max = rowsNumber;

		for (int i = 0; i < numberRowChars; i++)
		{
			int midPoint = min + (max - min + 1) / 2;
			if (str[i] == 'F')
			{
				max = midPoint - 1;
			}
			else
			{
				min = midPoint;
			}
		}

		row = min;	//Or row = max, both are the same

		min = 0; max = columnNumber;

		for (int i = numberRowChars; i < numberRowChars + numberColChars; i++)
		{
			int midPoint = min + (max - min + 1) / 2;
			if (str[i] == 'L')
			{
				max = midPoint - 1;
			}
			else
			{
				min = midPoint;
			}
		}

		col = min;	//Or col = max, both are the same

		int id = row * 8 + col;

		seatIds.push_back(id);

		if (id > maxId)
		{
			maxId = id;
		}
	}


	//Not the best way to find the element, but efficient enough with the input size
	for (int i = 1; i < maxId; i++)
	{
		//Find id (it shouln't be on the list)
		if (std::find(seatIds.begin(), seatIds.end(), i) != seatIds.end())
		{
			//Id included on the list
			continue;
		}

		//Find previous seat
		if (std::find(seatIds.begin(), seatIds.end(), i - 1) == seatIds.end())
		{
			//Previous not found
			continue;
		}

		//Find next seat
		if (std::find(seatIds.begin(), seatIds.end(), i + 1) == seatIds.end())
		{
			//Next not found
			continue;
		}

		output = i;
	}

	return std::to_string(output);
}