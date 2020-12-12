#include "Day12.h"

#include <stdlib.h>

std::string Day12::part1()
{
	auto input = loadFileAsStringList(pathToInput1);

	int posX = 0, posY = 0;
	int currentDir = 1;		// 0 - N, 1 - E, 2 - S, 3 - W

	for (auto& line : input)
	{
		int value = std::stoi(line.substr(1, line.size() - 1));
		int steps = 0;
		switch (line[0])
		{
		case 'N':
			posY += value;
			break;
		case 'S':
			posY -= value;
			break;
		case 'E':
			posX += value;
			break;
		case 'W':
			posX -= value;
			break;
		case 'R':
			steps = value / 90;
			currentDir = (currentDir + steps) % 4;
			break;
		case 'L':
			steps = value / 90;
			//CurrentDir is multiplied by 4 * step so that the left side of the mod is positive
			currentDir = currentDir + 4 * steps;
			currentDir = (currentDir - steps) % 4;
			break;
		case 'F':
			if (currentDir == 0)
			{
				posY += value;
			}
			else if (currentDir == 1)
			{
				posX += value;
			}
			else if (currentDir == 2)
			{
				posY -= value;
			}
			else
			{
				posX -= value;
			}
		}

	}

	return std::to_string(abs(posY) + abs(posX));
}

std::string Day12::part2()
{
	auto input = loadFileAsStringList(pathToInput1);

	int posX = 0, posY = 0;
	int posWX = 10, posWY = 1;	//Waypoint position

	for (auto& line : input)
	{
		int value = std::stoi(line.substr(1, line.size() - 1));
		int steps = 0;
		switch (line[0])
		{
		case 'N':
			posWY += value;
			break;
		case 'S':
			posWY -= value;
			break;
		case 'E':
			posWX += value;
			break;
		case 'W':
			posWX -= value;
			break;
		case 'R':
			value %= 360;
			if (value == 90)
			{
				int temp = posWX;
				posWX = posWY;
				posWY = -temp;
			}
			else if (value == 180)
			{
				posWX = -posWX;
				posWY = -posWY;
			}
			else if (value == 270)
			{
				posWX = -posWX;
				posWY = -posWY;
				int temp = posWX;
				posWX = posWY;
				posWY = -temp;
			}
			break;
		case 'L':
			if (value == 90)
			{
				int temp = posWX;
				posWX = -posWY;
				posWY = temp;
			}
			else if (value == 180)
			{
				posWX = -posWX;
				posWY = -posWY;
			}
			else if (value == 270)
			{
				posWX = -posWX;
				posWY = -posWY;
				int temp = posWX;
				posWX = -posWY;
				posWY = temp;
			}
			break;
		case 'F':
			posX += value * posWX;
			posY += value * posWY;
		}

	}

	return std::to_string(abs(posY) + abs(posX));
}
