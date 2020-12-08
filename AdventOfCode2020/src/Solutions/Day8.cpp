#include "Day8.h"

#include<unordered_map>

std::string Day8::part1()
{
	std::vector<std::string> memory = loadFileAsStringList(pathToInput1);
	int acc = 0;

	runProgram(memory, acc);

	return std::to_string(acc);
}

std::string Day8::part2()
{
	std::vector<std::string> memory = loadFileAsStringList(pathToInput2);

	for (auto& instruction : memory)
	{
		int acc = 0;
		if (instruction.substr(0, 3) == "nop")
		{
			//Change to jmp
			instruction = "jmp" + instruction.substr(3, instruction.size() - 3);
			if (runProgram(memory, acc))
			{
				return std::to_string(acc);
			}
			//Restore instruction
			instruction = "nop" + instruction.substr(3, instruction.size() - 3);
		}
		else if (instruction.substr(0, 3) == "jmp")
		{
			//Change to jmp
			instruction = "nop" + instruction.substr(3, instruction.size() - 3);
			if (runProgram(memory, acc))
			{
				return std::to_string(acc);
			}
			//Restore instruction
			instruction = "jmp" + instruction.substr(3, instruction.size() - 3);
		}
	}
}

bool Day8::runProgram(std::vector<std::string>& program, int& acc)
{
	int programCounter = -1;

	std::vector<int> vistiedInstructions;

	while (programCounter < int(program.size()) - 1)
	{
		programCounter++;


		//Exit BEFORE the first repeated instruction is executed
		if (std::find(vistiedInstructions.begin(), vistiedInstructions.end(), programCounter) != vistiedInstructions.end())
		{
			return false;
		}

		//Set this instruction to visited
		vistiedInstructions.push_back(programCounter);

		std::string& instruction = program[programCounter];

		auto instructionSplit = split(instruction, " ");

		if (instructionSplit[0] == "nop")	//Nop: increase PC and continue with the next instruction
		{
			//Do nothing
		}
		else if (instructionSplit[0] == "acc")
		{
			acc += std::stoi(instructionSplit[1]);
		}
		else if (instructionSplit[0] == "jmp")
		{
			programCounter += (std::stoi(instructionSplit[1]) - 1);	//The PC has already been increased by 1
		}
	}
	return true;
}