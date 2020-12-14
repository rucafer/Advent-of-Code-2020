#include "Day13.h"

#include <limits>
#include <map>

std::string Day13::part1()
{
	auto input = loadFileAsStringList(pathToInput1);

	int initialNumber = std::stoi(input[0]);

	int firstBusTime = std::numeric_limits<int>::max();
	int firstBusID = 0;

	for (auto& IDstr: split(input[1], ","))
	{
		if (IDstr != "x")
		{
			int ID = std::stoi(IDstr);

			int nextTime = initialNumber + (ID - (initialNumber % ID));
			if (nextTime < firstBusTime)
			{
				firstBusTime = nextTime;
				firstBusID = ID;
			}
		}
	}

	return std::to_string(firstBusID * (firstBusTime - initialNumber));
}

std::string Day13::part2()
{
	auto input = split(loadFileAsStringList(pathToInput2)[1], ",");

	std::vector<int> ids;
	std::vector<int> remainders;

	int offset = 0;
	for (auto& id : input)
	{
		if (id != "x")
		{
			int idInt = std::stoi(id);
			ids.push_back(idInt);
			remainders.push_back((idInt - offset) % idInt);	//If you use offset as the remainder you get the opposite order
		}
		offset++;
	}

	//Chinese remainders implementation
	/*

	| x = b1 mod n1
	| .
	| .					--> x = sum(bi*Ni*xi)	with N = n1*...*ni, Ni = N/ni and Ni*xi = 1 mod ni
	| .
	| x = bi mod ni
	
	*/

	long long N = 1;
	for (int id : ids)
	{
		N *= id;
	}

	long long x = 0;

	for (int i = 0; i < ids.size(); i++)
	{
		x += remainders[i] * N / ids[i] * findxi(N, ids[i]);
	}

	return std::to_string(x % N);
}

long long Day13::findxi(long long N, int ni)
{
	//Find xi so that Ni*xi = 1 mod ni

	long long Ni = N / ni;
	
	Ni %= ni;

	for (long long xi = 1; xi < ni; xi++)
	{
		if ((Ni * xi) % ni == 1)
		{
			return xi;
		}
	}

	//Error
	return -1;
}
