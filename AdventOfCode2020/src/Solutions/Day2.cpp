#include "Day2.h"

std::string Day2::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);
	
	//Correct passwords count
	int output = 0;

	for (std::string line : input)
	{
		size_t numberSeparatorIndex = line.find_first_of('-');
		if (numberSeparatorIndex == std::string::npos)
		{
			continue;
		}
		//Space before the letter
		size_t spaceIndex = line.find_first_of(' ', numberSeparatorIndex);


		int min = std::stoi(line.substr(0, numberSeparatorIndex));
		int max = std::stoi(line.substr(numberSeparatorIndex + 1, spaceIndex - numberSeparatorIndex - 1));
		char letter = line[spaceIndex + 1];

		//Space before the password
		spaceIndex = line.find_first_of(' ', spaceIndex + 1);
		std::string password = line.substr(spaceIndex + 1);


		int count = 0;
		for (char c : password)
		{
			if (c == letter)
			{
				count++;
			}
		}

		if (count >= min && count <= max)
		{
			output++;
		}

	}

	return std::to_string(output);
}

std::string Day2::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput2);

	//Correct passwords count
	int output = 0;

	for (std::string line : input)
	{
		size_t numberSeparatorIndex = line.find_first_of('-');
		if (numberSeparatorIndex == std::string::npos)
		{
			continue;
		}
		//Space before the letter
		size_t spaceIndex = line.find_first_of(' ', numberSeparatorIndex);

		//Convert indices to "index zero"
		int index1 = std::stoi(line.substr(0, numberSeparatorIndex)) - 1;
		int index2 = std::stoi(line.substr(numberSeparatorIndex + 1, spaceIndex - numberSeparatorIndex - 1)) - 1;
		char letter = line[spaceIndex + 1];

		//Space before the password
		spaceIndex = line.find_first_of(' ', spaceIndex + 1);
		std::string password = line.substr(spaceIndex + 1);

		char c1 = password[index1];
		char c2 = password[index2];

		if (c1 != c2 && (c1 == letter || c2 == letter))
		{
			output++;
		}

	}

	return std::to_string(output);
}