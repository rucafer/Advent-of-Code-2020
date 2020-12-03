#include "Day3.h"

std::string Day3::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::string result = std::to_string(getTreeCount(input, 3, 1));

	if (writeDebuggingInfo)
	{
		part1DebuggingInfo = debuggingOutput;
		debuggingOutput = "";	//Reset the debugginOutput for the next part
	}

	return result;
}

std::string Day3::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput2);

	long long output = 1;
 
	output *= (long long)getTreeCount(input, 1, 1);
	output *= (long long)getTreeCount(input, 3, 1);
	output *= (long long)getTreeCount(input, 5, 1);
	output *= (long long)getTreeCount(input, 7, 1);
	output *= (long long)getTreeCount(input, 1, 2);

	if (writeDebuggingInfo)
	{
		part2DebuggingInfo = debuggingOutput;
	}

	return std::to_string(output);
}

int Day3::getTreeCount(const std::vector<std::string>& input, int slopeRight, int slopeDown)
{

	if (writeDebuggingInfo)	//Write debug output header
	{
		debuggingOutput += "\n\n Input: slope Right: " + std::to_string(slopeRight) + " slope Down: " + std::to_string(slopeDown) + "\n\n";
	}

	const int steps = input.size() % slopeDown == 0 ? input.size() / slopeDown - 1 : input.size() / slopeDown;	//Number of steps (iterations) of the getTreeCountAlgorithm
	const int maxX = steps * slopeRight;
	const int repetitions = maxX / input[0].size();	//Number of times the row is repeated to the right

	int treesHit = 0;

	int posX = slopeRight, posY = slopeDown;	//The start positions is ignored (it never has a tree)

	for (int i = 0; i < input.size(); i++)
	{
		if (posY == i)
		{
			//A for loop is used instead of mod operator because it allows printing the whole "forest"
			for (int j = 0; j <= repetitions; j++)
			{
				std::string row = input[i];
				if (posX >= j * row.size() && posX < (j + 1) * row.size())
				{
					int index = posX - j * row.size();
					if (row[index] == '#')
					{
						row[index] = 'X';
						treesHit++;
					}
					else
					{
						row[index] = 'O';
					}
				}
				if (writeDebuggingInfo)
				{
					debuggingOutput += row;
				}
			}

			posX += slopeRight;
			posY += slopeDown;
		}
		else if(writeDebuggingInfo)
		{
			for (int j = 0; j <= repetitions; j++)
			{
				debuggingOutput += input[i];
			}
		}
		if (writeDebuggingInfo)
		{
			debuggingOutput += "\n";
		}
	}
	return treesHit;
}