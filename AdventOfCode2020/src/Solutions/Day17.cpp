#include "Day17.h"

std::string Day17::part1()
{
    auto input = loadFileAsStringList(pathToInput1);

    std::vector<std::vector<std::vector<char>>> grid;   //grid[z][y][x]
    int indexOfStartingLayer = 0;

    grid.emplace_back();    //Add layer 0
    
    int result = 0;

    for (auto& line : input)
    {
        std::vector<char> lineArray;
        for (char c : line)
        {
            lineArray.push_back(c);
        }
        grid[0].push_back(lineArray);
    }


    for (int i = 0; i < 6; i++)
    {
        //Make grid bigger so that new active points can fit
        for (auto& layer : grid)
        {
            for (auto& line : layer)
            {
                //Add an inactive element at the beginning and end of each line
                line.insert(line.begin(), '.');
                line.push_back('.');
            }

            //Add a new line at the beginning and the end of each layer
            std::vector<char> newLine(layer[0].size(), '.');
            layer.insert(layer.begin(), newLine);
            layer.push_back(newLine);
        }

        std::vector<std::vector<char>> newLayer(grid[0].size(), std::vector<char>(grid[0][0].size(), '.'));
        grid.insert(grid.begin(), newLayer);
        grid.push_back(newLayer);
        indexOfStartingLayer++;

        std::vector<std::vector<std::vector<char>>> copy = grid;

        for (int z = 0; z < grid.size(); z++)
        {
            for (int y = 0; y < grid[0].size(); y++)
            {
                for (int x = 0; x < grid[0][0].size(); x++)
                {
                    int neighbors = findNumberOfNeighbors(grid, x, y, z);
                    if (grid[z][y][x] == '#' && (neighbors != 2 && neighbors != 3))
                    {
                        copy[z][y][x] = '.';
                    }
                    else if (grid[z][y][x] == '.' && neighbors == 3)
                    {
                        copy[z][y][x] = '#';
                    }
                }
            }
        }

        grid = copy;

        part1DebuggingInfo += "After " + std::to_string(i + 1) + " cycles \n\n" + getGridAsString(grid, indexOfStartingLayer);
    }


    for (int z = 0; z < grid.size(); z++)
    {
        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid[0][0].size(); x++)
            {
                if (grid[z][y][x] == '#')
                {
                    result++;
                }
            }
        }
    }

    return std::to_string(result);
}

//Not very efficient, is an n^4 algorithm (~10s)
std::string Day17::part2()
{
    auto input = loadFileAsStringList(pathToInput1);

    std::vector<std::vector<std::vector<std::vector<char>>>> grid;   //grid[w][z][y][x]
    int indexOfStartingLayer = 0;

    grid.emplace_back();    //Add first cube
    grid[0].emplace_back(); //Add first layer to first cube

    int result = 0;

    for (auto& line : input)
    {
        std::vector<char> lineArray;
        for (char c : line)
        {
            lineArray.push_back(c);
        }
        grid[0][0].push_back(lineArray);
    }


    for (int i = 0; i < 6; i++)
    {
        //Make grid bigger so that new active points can fit
        for (auto& cube : grid)
        {
            for (auto& layer : cube)
            {
                for (auto& line : layer)
                {
                    //Add an inactive element at the beginning and end of each line
                    line.insert(line.begin(), '.');
                    line.push_back('.');
                }

                //Add a new line at the beginning and the end of each layer
                std::vector<char> newLine(layer[0].size(), '.');
                layer.insert(layer.begin(), newLine);
                layer.push_back(newLine);
            }

            std::vector<std::vector<char>> newLayer(grid[0][0].size(), std::vector<char>(grid[0][0][0].size(), '.'));
            cube.insert(cube.begin(), newLayer);
            cube.push_back(newLayer);
            indexOfStartingLayer++;
        }

        std::vector<std::vector<std::vector<char>>> newCube(grid[0].size(), std::vector<std::vector<char>>(grid[0][0][0].size(), std::vector<char>(grid[0][0].size(), '.')));
        grid.insert(grid.begin(), newCube);
        grid.push_back(newCube);

        std::vector<std::vector<std::vector<std::vector<char>>>> copy = grid;

        for(int w = 0; w < grid.size(); w++)
        for (int z = 0; z < grid[0].size(); z++)
        {
            for (int y = 0; y < grid[0][0].size(); y++)
            {
                for (int x = 0; x < grid[0][0][0].size(); x++)
                {
                    int neighbors = findNumberOfNeighbors(grid, x, y, z, w);
                    if (grid[w][z][y][x] == '#' && (neighbors != 2 && neighbors != 3))
                    {
                        copy[w][z][y][x] = '.';
                    }
                    else if (grid[w][z][y][x] == '.' && neighbors == 3)
                    {
                        copy[w][z][y][x] = '#';
                    }
                }
            }
        }

        grid = copy;
    }


    for(int w = 0; w < grid.size(); w++)
    for (int z = 0; z < grid[0].size(); z++)
    {
        for (int y = 0; y < grid[0][0].size(); y++)
        {
            for (int x = 0; x < grid[0][0][0].size(); x++)
            {
                if (grid[w][z][y][x] == '#')
                {
                    result++;
                }
            }
        }
    }

    return std::to_string(result);
}

std::string Day17::getGridAsString(const std::vector<std::vector<std::vector<char>>>& grid, int indexOfStartingLayer)
{
    std::string output = "";

    for (int i = 0; i < grid.size(); i++)
    {
        auto& layer = grid[i];

        output += "z=" + std::to_string(i - indexOfStartingLayer) + '\n';
        for (auto& line : layer)
        {
            for (char c : line)
            {
                output += c;
            }
            output += '\n';
        }
    }

    return output;
}

int Day17::findNumberOfNeighbors(const std::vector<std::vector<std::vector<char>>>& grid, int x, int y, int z)
{
    const int neighbors[26][3] = { {0,0,1}, {0,0,-1}, {0,1,0}, {0,1,1}, {0,1,-1}, {0,-1,0}, {0,-1,1}, {0,-1,-1},
                                    {1,0,0}, {1,0,1}, {1,0,-1}, {1,1,0}, {1,1,1}, {1,1,-1}, {1,-1,0}, {1,-1,1}, {1,-1,-1},
                                    {-1,0,0}, {-1,0,1}, {-1,0,-1}, {-1,1,0}, {-1,1,1}, {-1,1,-1}, {-1,-1,0}, {-1,-1,1}, {-1,-1,-1} };

    int count = 0;

    for (auto& neighbor : neighbors)
    {
        int newX = x + neighbor[0];
        int newY = y + neighbor[1];
        int newZ = z + neighbor[2];
        
        //Check if the neighbor is valid (if it's not on the grid, its innactive)
        if (newX >= 0 && newY >= 0 && newZ >= 0)
        {
            if (newZ < grid.size() && newY < grid[0].size() && newX < grid[0][0].size())
            {
                if (grid[newZ][newY][newX] == '#')
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int Day17::findNumberOfNeighbors(const std::vector<std::vector<std::vector<std::vector<char>>>>& grid, int x, int y, int z, int w)
{
    const int neighbors[80][4] = { {0,0,0,1}, {0,0,0,-1}, {0,0,1,0}, {0,0,1,1}, {0,0,1,-1}, {0,0,-1,0}, {0,0,-1,1}, {0,0,-1,-1},
                                    {0,1,0,0}, {0,1,0,1}, {0,1,0,-1}, {0,1,1,0}, {0,1,1,1}, {0,1,1,-1}, {0,1,-1,0}, {0,1,-1,1}, {0,1,-1,-1},
                                    {0,-1,0,0}, {0,-1,0,1}, {0,-1,0,-1}, {0,-1,1,0}, {0,-1,1,1}, {0,-1,1,-1}, {0,-1,-1,0}, {0,-1,-1,1}, {0,-1,-1,-1},
                                    {1,0,0,0}, {1,0,0,1}, {1,0,0,-1}, {1,0,1,0}, {1,0,1,1}, {1,0,1,-1}, {1,0,-1,0}, {1,0,-1,1}, {1,0,-1,-1},
                                    {1,1,0,0}, {1,1,0,1}, {1,1,0,-1}, {1,1,1,0}, {1,1,1,1}, {1,1,1,-1}, {1,1,-1,0}, {1,1,-1,1}, {1,1,-1,-1},
                                    {1,-1,0,0}, {1,-1,0,1}, {1,-1,0,-1}, {1,-1,1,0}, {1,-1,1,1}, {1,-1,1,-1}, {1,-1,-1,0}, {1,-1,-1,1}, {1,-1,-1,-1},
                                    {-1,0,0,0}, {-1,0,0,1}, {-1,0,0,-1}, {-1,0,1,0}, {-1,0,1,1}, {-1,0,1,-1}, {-1,0,-1,0}, {-1,0,-1,1}, {-1,0,-1,-1},
                                    {-1,1,0,0}, {-1,1,0,1}, {-1,1,0,-1}, {-1,1,1,0}, {-1,1,1,1}, {-1,1,1,-1}, {-1,1,-1,0}, {-1,1,-1,1}, {-1,1,-1,-1},
                                    {-1,-1,0,0}, {-1,-1,0,1}, {-1,-1,0,-1}, {-1,-1,1,0}, {-1,-1,1,1}, {-1,-1,1,-1}, {-1,-1,-1,0}, {-1,-1,-1,1}, {-1,-1,-1,-1}};

    int count = 0;

    for (auto& neighbor : neighbors)
    {
        int newX = x + neighbor[0];
        int newY = y + neighbor[1];
        int newZ = z + neighbor[2];
        int newW = w + neighbor[3];

        //Check if the neighbor is valid (if it's not on the grid, its innactive)
        if (newX >= 0 && newY >= 0 && newZ >= 0 && newZ > 0)
        {
            if (newW < grid.size() && newZ < grid[0].size() && newY < grid[0][0].size() && newX < grid[0][0][0].size())
            {
                if (grid[newW][newZ][newY][newX] == '#')
                {
                    count++;
                }
            }
        }
    }
    return count;
}
