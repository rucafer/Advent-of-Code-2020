#include "Day6.h"

std::string Day6::part1()
{
	std::string input = loadFileAsString(pathToInput1);

	int output = 0;

	for (auto& group : split(input, "\n\n"))
	{
		int count = 0;
		bool questions[26];	//Answers to every question
		std::fill_n(questions, 26, false);	//Initialize answers to "no"
		
		for (auto& person : split(group, "\n"))
		{
			for (char question : person)
			{
				//Get array index (a --> 0, b --> 1, ... , z --> 25)
				int index = question - 'a';
				questions[index] = true;
			}
		}

		for (int i = 0; i < 26; i++)	//Count "yes" answers
		{
			if (questions[i])
			{
				count++;
			}
		}

		output += count;
	}

	return std::to_string(output);
}

std::string Day6::part2()
{
	std::string input = loadFileAsString(pathToInput2);

	int output = 0;

	for (auto& group : split(input, "\n\n"))
	{
		int count = 0;
		std::vector<char> answers;

		bool firstPerson = true;

		for (auto& person : split(group, "\n"))
		{
			if (firstPerson)	//All answers from person 1 will be stored.
								//If one of this answers isn't found in next persons' answers, they will be removed from the list
			{
				for (char question : person)
				{
					answers.push_back(question);
				}
				
				firstPerson = false;
			}
			else
			{
				std::vector<char> answersCopy = answers;	//In order to delete elements from the vector we need a copy
															//so that the iterator doesn't become invalid
				for (char question : answersCopy)
				{
					if (person.find_first_of(question) == std::string::npos)
					{
						//Delete an element from answers array if it's not present in the current person
						answers.erase(std::find(answers.begin(), answers.end(), question));
					}
				}
			}
		}

		output += (int)answers.size();
	}

	return std::to_string(output);
}