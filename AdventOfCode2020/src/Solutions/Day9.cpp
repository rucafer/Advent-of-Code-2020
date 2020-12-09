#include "Day9.h"

#include <algorithm>

std::string Day9::part1()
{
	std::vector<long long> input = loadFileAsLongList(pathToInput1);

	const int preambleSize = 25;

	for (int i = preambleSize; i < input.size(); i++)
	{
		bool found = false;
		for (int j = i - preambleSize; j < i; j++)
		{
			for (int k = i - preambleSize; k < i; k++)
			{
				if (j != k)
				{
					if (input[i] == input[j] + input[k])
					{
						found = true;
					}
				}
			}
		}
		if (!found)
		{
			return std::to_string(input[i]);
		}
	}

	return "Solution not found";
}

std::string Day9::part2()
{
	std::vector<long long> input = loadFileAsLongList(pathToInput2);

	const int preambleSize = 25;

	long long invalidNumber = 0;

	for (int i = preambleSize; i < input.size(); i++)
	{
		bool found = false;
		for (int j = i - preambleSize; j < i; j++)
		{
			for (int k = i - preambleSize; k < i; k++)
			{
				if (j != k)
				{
					if (input[i] == input[j] + input[k])
					{
						found = true;
					}
				}
			}
		}
		if (!found)
		{
			invalidNumber = input[i];
		}
	}

	for (int first = 0; first < input.size(); first++)
	{
		//Skip the invalid number
		if (input[first] == invalidNumber)
		{
			continue;
		}

		int last = first;
		long long sum = 0;
		while (sum < invalidNumber && last < input.size())
		{
			sum += input[last];
			last++;
		}

		//Solution found
		if (sum == invalidNumber)
		{
			return std::to_string(*std::max_element(input.begin() + first, input.begin() + last - 1) +
				*std::min_element(input.begin() + first, input.begin() + last - 1));
		}
	}

	return "Solution not found";
}