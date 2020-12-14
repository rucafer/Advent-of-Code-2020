#include "Day14.h"

#include <unordered_map>
#include <math.h>

std::string Day14::part1()
{
	auto input = loadFileAsStringList(pathToInput1);
	std::unordered_map<uint64_t, uint64_t> memory;	//Key: address value: value
	uint64_t andMask = 0;	//Mask for 0
	uint64_t orMask = 0;		//Mask for 1

	for (auto& line : input)
	{
		size_t numberStartPos = 0;
		size_t indexStartPos = 0;
		size_t indexEndPos = 0;

		numberStartPos = line.find_first_of('=') + 2;
		indexStartPos = line.find_first_of('[') + 1;
		indexEndPos = line.find_first_of(']');

		if (line.find("mask") != std::string::npos)
		{
			auto maskStr = line.substr(numberStartPos, line.size() - numberStartPos);

			andMask = -1;
			orMask = 0;


			for (char c : maskStr)
			{
				//Shift masks
				andMask <<= 1;
				orMask <<= 1;

				switch (c)
				{
				case 'X':
					andMask += 1;	//And with 1 and or with 0 (same value)
					break;
				case '1':
					andMask += 1;	//And with 1 (same value)
					orMask += 1;	//Or with 1 (forces 1)
					break;
				case '0':
					break;			//Or with 0 (same value) and and with 0 (forces 0)
				}
			}
		}
		else
		{
			uint64_t index = std::stoi(line.substr(indexStartPos, indexEndPos - indexStartPos));
			uint64_t value = std::stoul(line.substr(numberStartPos, line.size() - numberStartPos));
			
			value &= andMask;
			value |= orMask;

			memory[index] = value;
		}
	}


	uint64_t result = 0;
	for (auto element : memory)
	{
		result += element.second;
	}
	return std::to_string(result);
}

std::string Day14::part2()
{
	auto input = loadFileAsStringList(pathToInput2);

	std::vector<std::string> indices;
	std::vector<uint64_t> values;


	std::string mask;

	uint64_t result = 0;

	for (auto& line : input)
	{
		size_t numberStartPos = 0;
		size_t indexStartPos = 0;
		size_t indexEndPos = 0;

		numberStartPos = line.find_first_of('=') + 2;
		indexStartPos = line.find_first_of('[') + 1;
		indexEndPos = line.find_first_of(']');

		if (line.find("mask") != std::string::npos)
		{
			mask = line.substr(numberStartPos, line.size() - numberStartPos);
		}
		else
		{
			std::string index = intToBinaryString(std::stoi(line.substr(indexStartPos, indexEndPos - indexStartPos)));
			uint64_t value = std::stoul(line.substr(numberStartPos, line.size() - numberStartPos));

			for (int i = 0; i < 36; i++)
			{
				if (mask[i] == '1')
				{
					index[i] = '1';
				}
				else if (mask[i] == 'X')
				{
					index[i] = 'X';
				}
			}

			addToMemory(indices, values, index, value);
		}
	}

	for (int i = 0; i < indices.size(); i++)
	{
		uint64_t numberOfX = std::count(indices[i].begin(), indices[i].end(), 'X');

		result += (uint64_t) pow((uint64_t)2, numberOfX) * values[i];
	}

	return std::to_string(result);
}

void Day14::addToMemory(std::vector<std::string>& indices, std::vector<uint64_t>& values, const std::string& newIndex, uint64_t newValue)
{
	int i = 0;

	while (i < indices.size())
	{
		std::string oldIndex = indices[i];
		uint64_t oldValue = values[i];

		if (intersect(oldIndex, newIndex)) 
		{
			if (oldIndex.find_first_of('X') != std::string::npos)
			{
				size_t xPos = oldIndex.find_first_of('X');

				//Create two copies and delete original
				std::string oldIndex0 = oldIndex;
				std::string oldIndex1 = oldIndex;
				auto indicesIt = indices.begin() + i;
				auto valuesIt = values.begin() + i;
				indices.erase(indicesIt);

				//Add new versions, changing the first X by 0 and 1
				oldIndex0[xPos] = '0';
				oldIndex1[xPos] = '1';
				indices.insert(indices.begin() + i, oldIndex0);
				indices.insert(indices.begin() + i, oldIndex1);
				values.insert(valuesIt, oldValue);
			}
			else
			{
				indices.erase(indices.begin() + i);
				values.erase(values.begin() + i);
			}
		}
		else
		{
			i++;
		}
	}

	indices.push_back(newIndex);
	values.push_back(newValue);
}

bool Day14::intersect(const std::string& oldIndex, const std::string& newIndex)
{
	for (int i = 0; i < oldIndex.size(); i++)
	{
		if (oldIndex[i] != 'X' && newIndex[i] != 'X' && oldIndex[i] != newIndex[i])
		{
			return false;
		}
	}

	return true;
}

std::string Day14::intToBinaryString(uint64_t number)
{
	std::string result(36, ' ');

	for (int i = 1; i <= 36; i++)
	{
		result[(size_t)36 - i] = number % 2 == 0 ? '0' : '1';
		number /= 2;
	}

	return result;
}