#include "Day16.h"

#include<algorithm>

std::string Day16::part1()
{
	auto input = loadFileAsString(pathToInput1);

	auto header = split(input, "\n\n")[0];

	std::vector<Range> ranges;

	int solution = 0;

	for (auto& range : split(header, "\n"))
	{
		ranges.push_back(loadRange(range));
	}

	size_t nearbyTicketsPos = input.find("nearby tickets:");

	for (auto& line : split(input.substr(nearbyTicketsPos + 16, input.size() - nearbyTicketsPos - 1), "\n"))
	{
		for (auto& value : split(line, ","))
		{
			bool valid = false;
			int number = std::stoi(value);
			for (Range range : ranges)
			{
				if (inRange(number, range))
				{
					valid = true;
					break;
				}
			}

			if (valid == false)
			{
				solution += number;
			}
		}
	}
	return std::to_string(solution);
}

std::string Day16::part2()
{
	auto input = loadFileAsString(pathToInput2);

	auto header = split(input, "\n\n")[0];

	std::vector<Range> ranges;

	std::vector<std::vector<int>> validTickets;

	for (auto& range : split(header, "\n"))
	{
		ranges.push_back(loadRange(range));
	}

	size_t nearbyTicketsPos = input.find("nearby tickets:");

	for (auto& line : split(input.substr(nearbyTicketsPos + 16, input.size() - nearbyTicketsPos - 1), "\n"))
	{
		bool valid = true;
		std::vector<int> values;
		for (auto& value : split(line, ","))
		{
			bool rangeFound = false;
			int number = std::stoi(value);
			for (Range range : ranges)
			{
				if (inRange(number, range))
				{
					rangeFound = true;
					values.push_back(number);
					break;
				}
			}

			if (rangeFound == false)
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			validTickets.push_back(values);
		}
	}

	//Load your ticket
	size_t yourTicketPos = input.find("your ticket:");
	
	validTickets.emplace_back();	//Your ticket is the last of the list
	for (auto value : split(input.substr(yourTicketPos + 13, nearbyTicketsPos - yourTicketPos - 15), ","))
	{
		(*validTickets.rbegin()).push_back(std::stoi(value));
	}


	std::vector<std::vector<int>> columnsPerRange;	//Valid columns index for range i
	for (int i =  0; i < ranges.size(); i++)
	{
		std::vector<int> validColumns;
		for (int j = 0; j < validTickets[0].size(); j++)
		{
			bool valid = true;

			for (auto ticket : validTickets)
			{
				if (!inRange(ticket[j], ranges[i]))
				{
					valid = false; 
					break;
				}
			}

			if (valid)
			{
				validColumns.push_back(j);
			}
		}
		columnsPerRange.push_back(validColumns);
	}

	std::vector<int> rangeOfColumn(ranges.size(), -1);	//Column i represents the range rangeOfColumn[i]
	std::vector<int> remainingIndices;
	for (int i = 0; i < ranges.size(); i++)
	{
		remainingIndices.push_back(i);
	}

	while (!remainingIndices.empty())
	{
		for (int index : remainingIndices)
		{
			if (columnsPerRange[index].size() == 1)
			{
				int column = columnsPerRange[index][0];
				rangeOfColumn[column] = index;

				//Remove that column from the list of valid columns for each range
				for (auto& columnsList : columnsPerRange)
				{
					auto pos = std::find(columnsList.begin(), columnsList.end(), column);
					if (pos != columnsList.end())
					{
						columnsList.erase(pos);
					}
				}

				//Remove index form remainingIndices
				remainingIndices.erase(std::remove(remainingIndices.begin(), remainingIndices.end(), index));

				break;
			}
		}
	}

	long long solution = 1;

	for (int i = 0; i < 6; i++)	//Departure fields are the 6 first ones
	{
		int column = std::distance(rangeOfColumn.begin(), std::find(rangeOfColumn.begin(), rangeOfColumn.end(), i));
		solution *= (*validTickets.rbegin())[column];
	}


	return std::to_string(solution);
}

Range Day16::loadRange(const std::string& range)
{
	Range result;

	size_t colonPos = range.find_first_of(':');
	size_t orPos = range.find(" or ");
	size_t separator1 = range.find_first_of('-');
	size_t separator2 = range.find_last_of('-');

	result.name = range.substr(0, colonPos);
	result.min0 = std::stoi(range.substr(colonPos + 2, separator1 - colonPos - 2));
	result.max0 = std::stoi(range.substr(separator1 + 1, orPos - separator1));

	result.min1 = std::stoi(range.substr(orPos + 4, separator2 - orPos - 4));
	result.max1 = std::stoi(range.substr(separator2 + 1, range.size() - separator1));

	return result;
}

bool Day16::inRange(int number, const Range& range)
{
	return (number >= range.min0 && number <= range.max0) || (number >= range.min1 && number <= range.max1);
}