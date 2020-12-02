#include "Day1.h"

std::string Day1::part1()
{
	std::vector<int> input = loadFileAsIntList(pathToInput1);
	

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input.size(); j++)
		{
			if (i != j)
			{
				if (input[i] + input[j] == 2020)
				{
					return std::to_string(input[i] * input[j]);
				}
			}
		}
	}

	return "numberNotFound";
}

std::string Day1::part2()
{
	std::vector<int> input = loadFileAsIntList(pathToInput1);


	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input.size(); j++)
		{
			for (int z = 0; z < input.size(); z++)
			{
				if (i != j && j != z)
				{
					if (input[i] + input[j] + input[z]== 2020)
					{
						return std::to_string(input[i] * input[j] * input[z]);
					}
				}
			}
		}
	}

	return "numberNotFound";
}