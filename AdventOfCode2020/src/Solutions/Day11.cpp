#include "Day11.h"

std::string Day11::part1()
{
	auto input = loadFileAsStringList(pathToInput1);

	int output = 0;

	const int numberOfRows = (int)input.size();
	const int numberOfColumns = (int)input[0].size();

	//Create the table
	std::vector<std::vector<char>> table;

	for (int row = 0; row < numberOfRows; row++)
	{
		//Add empty row
		table.emplace_back();
		for (char element :input[row])
		{
			table[row].push_back(element);
		}
	}

	int changes = 0;	//Changes made in the last iteration

	int adjacentPos[8][2] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1},{0,-1}, {1,-1} };
	
	do
	{
		changes = 0;
		auto newTable = table;	//Table for the next iteration (current table can't be modified)
		for (int row = 0; row < numberOfRows; row++)
		{
			for (int column = 0; column < numberOfColumns; column++)
			{
				if (table[row][column] == 'L')
				{
					bool occupiedSeats = false;

					for (auto posDiff : adjacentPos)
					{
						int posX = row - posDiff[0];
						int posY = column - posDiff[1];

						if (posX >= 0 && posX < numberOfRows && posY >= 0 && posY < numberOfColumns)
						{
							if (table[posX][posY] == '#')
							{
								occupiedSeats = true;
							}
						}
					}

					if (!occupiedSeats)
					{
						newTable[row][column] = '#';
						output++;
						changes++;
					}
				}

				else if (table[row][column] == '#')
				{
					int emptySeats = 0;

					for (auto posDiff : adjacentPos)
					{
						int posX = row - posDiff[0];
						int posY = column - posDiff[1];

						if (posX >= 0 && posX < numberOfRows && posY >= 0 && posY < numberOfColumns && table[posX][posY] == '#')
						{
							emptySeats++;
						}
					}

					if (emptySeats >= 4)
					{
						newTable[row][column] = 'L';
						changes++;
						output--;
					}
				}
			}
		}

		table = newTable;
	} while (changes != 0);

	//Print debug info
	for (int row = 0; row < numberOfRows; row++)
	{
		for (int column = 0; column < numberOfColumns; column++)
		{
			part1DebuggingInfo += table[row][column];
		}
		part1DebuggingInfo += "\n";
	}


	return std::to_string(output);
}

std::string Day11::part2()
{
	auto input = loadFileAsStringList(pathToInput2);

	int output = 0;

	const int numberOfRows = (int)input.size();
	const int numberOfColumns = (int)input[0].size();

	//Create the table
	std::vector<std::vector<char>> table;

	for (int row = 0; row < numberOfRows; row++)
	{
		//Add empty row
		table.emplace_back();
		for (char element : input[row])
		{
			table[row].push_back(element);
		}
	}

	int changes = 0;	//Changes made in the last iteration

	do
	{
		changes = 0;
		auto newTable = table;	//Table for the next iteration (current table can't be modified)
		for (int row = 0; row < numberOfRows; row++)
		{
			for (int column = 0; column < numberOfColumns; column++)
			{
				if (table[row][column] == 'L')
				{
					if (countVisibleSeats(row, column, table) == 0)
					{
						newTable[row][column] = '#';
						changes++;
						output++;
					}
				}
				else if (table[row][column] == '#')
				{
					if (countVisibleSeats(row, column, table) >= 5)
					{
						newTable[row][column] = 'L';
						changes++;
						output--;
					}
				}
			}
		}

		table = newTable;
	} while (changes != 0);

	//Print debug info
	for (int row = 0; row < numberOfRows; row++)
	{
		for (int column = 0; column < numberOfColumns; column++)
		{
			part2DebuggingInfo += table[row][column];
		}
		part2DebuggingInfo += "\n";
	}


	return std::to_string(output);
}

int Day11::countVisibleSeats(int row, int column, const std::vector<std::vector<char>>& table)
{
	int count = 0;

	const int numberOfRows = (int)table.size();
	const int numberOfColumns = (int)table[0].size();

	int x, y;
	//Seats on the column
	//Up
	x = row;
	y = column + 1;
	while (y < numberOfColumns && table[x][y] == '.')
	{
		y++;
	}

	if (y < numberOfColumns && table[x][y] == '#')
	{
		count++;
	}

	//Down
	x = row;
	y = column - 1;
	while (y >= 0 && table[x][y] == '.')
	{
		y--;
	}

	if (y >= 0 && table[x][y] == '#')
	{
		count++;
	}

	//Seats on the row
	//Right
	x = row + 1;
	y = column;
	while (x < numberOfRows && table[x][y] == '.')
	{
		x++;
	}

	if (x < numberOfRows && table[x][y] == '#')
	{
		count++;
	}

	//Down
	x = row - 1;
	y = column;
	while (x >= 0 && table[x][y] == '.')
	{
		x--;
	}

	if (x >= 0 && table[x][y] == '#')
	{
		count++;
	}

	//Diagonals
	//Up right
	x = row + 1;
	y = column + 1;
	while (x < numberOfRows && y < numberOfColumns && table[x][y] == '.')
	{
		x++;
		y++;
	}

	if (x < numberOfRows && y < numberOfColumns && table[x][y] == '#')
	{
		count++;
	}

	//Down right
	x = row + 1;
	y = column - 1;
	while (x < numberOfRows && y >=0 && table[x][y] == '.')
	{
		x++;
		y--;
	}

	if (x < numberOfRows && y >= 0 && table[x][y] == '#')
	{
		count++;
	}

	//Down left
	x = row - 1;
	y = column - 1;
	while (x >= 0 && y >= 0 && table[x][y] == '.')
	{
		x--;
		y--;
	}

	if (x >= 0 && y >= 0 && table[x][y] == '#')
	{
		count++;
	}

	//Up left
	x = row - 1;
	y = column + 1;
	while (x >= 0 && y < numberOfColumns && table[x][y] == '.')
	{
		x--;
		y++;
	}

	if (x >= 0 && y < numberOfColumns && table[x][y] == '#')
	{
		count++;
	}

	return count;
}