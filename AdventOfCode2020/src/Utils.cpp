#include "Utils.h"

#include <string>

std::string getDayHeader(int dayNumber)
{
	std::string result = "\n\x1B[33m******************************\n*********** DAY ";
	if (dayNumber < 10)
	{
		result += " ";
	}
	result += std::to_string(dayNumber);
	
	result += " ***********\n******************************\033[0m\n";
	return result;
}



std::vector<int> loadFileAsIntList(const std::string& file)
{
	std::vector<int> result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			if (line.find_first_of(' ') == std::string::npos && line.size() > 0)
			{
				result.push_back(std::stoi(line));
			}
			else
			{
				size_t lastSpace = 0;
				while ((lastSpace = line.find_first_of(' ', lastSpace)) != std::string::npos)
				{
					size_t nextSpace = line.find_first_of(' ', lastSpace + 1);
					if (nextSpace == std::string::npos)
					{
						nextSpace = line.size();
					}
					std::string number = line.substr(lastSpace + 1, nextSpace - lastSpace - 1);
					if (number.size() > 0)
					{
						result.push_back(std::stoi(number));
					}
					lastSpace = nextSpace;
				}
			}
		}
	}
	return result;
}