#include "Day7.h"

#include <unordered_map>
#include <vector>
#include <queue>

std::string Day7::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);


	std::unordered_map<std::string, std::vector<std::string>> m_Children;	//Key: node, value: array of children of the node
	std::unordered_map<std::string, std::vector<std::string>> m_Parents;	//Key: node, value: array of parents of the node

	for (auto& line : input)
	{
		auto lineSplit = split(line, " contain ");
		std::string parent = lineSplit[0];
		size_t bagsPos = parent.find(" bag");
		parent = parent.substr(0, bagsPos);

		std::string children = lineSplit[1];

		//Ignore empty bags
		if (children == "no other bags.")
		{
			continue;
		}

		//Remove final dot
		children.erase(children.end() - 1);

		auto childrenWithNumber = split(children, ", ");

		std::vector<std::string>& childrenVector = m_Children[parent];

		for (auto& child : childrenWithNumber)
		{
			size_t spacePos = child.find_first_of(" ");
			size_t bagPos = child.find(" bag");
			child = child.substr(spacePos + 1, bagPos - (spacePos + 1));

			if (std::find(childrenVector.begin(), childrenVector.end(), child) == childrenVector.end())
			{
				childrenVector.push_back(child);

				std::vector<std::string>& parentsVector = m_Parents[child];
				if (std::find(parentsVector.begin(), parentsVector.end(), parent) == parentsVector.end())
				{
					parentsVector.push_back(parent);
				}
			}
		}
	}

	std::vector<std::string> result;

	//Queue that will store parents to be processed
	std::queue<std::string> parents;
	//Initial queue population
	for (auto& parent : m_Parents["shiny gold"])
	{
		parents.push(parent);
	}

	while (!parents.empty())
	{
		std::string parent = parents.front();
		parents.pop();

		//Only add the node to the solution and to the queue if it hasn't been visited before
		if (std::find(result.begin(), result.end(), parent) == result.end())
		{
			result.push_back(parent);

			//Add parents of the current parent to the queue
			for (auto& parent2 : m_Parents[parent])
			{
				parents.push(parent2);
			}
		}
	}
	return std::to_string(result.size());
}

std::string Day7::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::map<std::string, std::vector<Bag>> m_Children;	//Key: node, value: array of children of the node

	for (auto& line : input)
	{
		auto lineSplit = split(line, " contain ");
		std::string parent = lineSplit[0];
		size_t bagsPos = parent.find(" bag");
		parent = parent.substr(0, bagsPos);

		std::string children = lineSplit[1];

		//Ignore empty bags
		if (children == "no other bags.")
		{
			continue;
		}

		//Remove final dot
		children.erase(children.end() - 1);

		auto childrenWithNumber = split(children, ", ");

		std::vector<Bag>& childrenVector = m_Children[parent];

		for (auto& child : childrenWithNumber)
		{
			size_t spacePos = child.find_first_of(" ");
			size_t bagPos = child.find(" bag");

			Bag bag = { child.substr(spacePos + 1, bagPos - (spacePos + 1)), std::stoi(child.substr(0, spacePos)) };


			childrenVector.push_back(bag);
		}
	}

	return std::to_string(addBagsRecursive("shiny gold", m_Children) - 1);
}

int Day7::addBagsRecursive(const std::string& name, std::map<std::string, std::vector<Bag>>& map)
{
	int result = 1;

	//Base case
	if (map[name].size() == 0)
	{
		return 1;
	}

	for (Bag& bag : map[name])
	{
		result += bag.count * addBagsRecursive(bag.name, map);
	}

	return result;
}