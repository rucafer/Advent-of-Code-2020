#include "Day18.h"
#include <stack>

std::string Day18::part1()
{
    auto input = loadFileAsStringList(pathToInput1);
    long long total = 0;
    
    for (std::string& line : input)
    {
        std::stack<std::string> expressions;
        std::string currentStr = "";

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '(')
            {
                expressions.push(currentStr);
                currentStr = "";
            }
            else if (line[i] == ')')
            {
                long long parenthesesResult = solve(currentStr);
                currentStr = expressions.top() + std::to_string(parenthesesResult);
                expressions.pop();
            }
            else
            {
                currentStr += line[i];
            }
        }

        total += solve(currentStr);
    }

    return std::to_string(total);
}

std::string Day18::part2()
{
    auto input = loadFileAsStringList(pathToInput1);
    long long total = 0;

    for (std::string& line : input)
    {
        std::stack<std::string> expressions;
        std::string currentStr = "";

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '(')
            {
                expressions.push(currentStr);
                currentStr = "";
            }
            else if (line[i] == ')')
            {
                long long parenthesesResult = solve2(currentStr);
                currentStr = expressions.top() + std::to_string(parenthesesResult);
                expressions.pop();
            }
            else
            {
                currentStr += line[i];
            }
        }

        total += solve2(currentStr);
    }

    return std::to_string(total);
}

long long Day18::solve(std::string expression)
{
    long long result = 0;
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());

    std::vector<std::string> numbers;

    numbers = split(expression, "+");
    std::vector<char> operations(numbers.size() - 1, '+');  //number i and i+1 are related by the operation i

    for (int i = 0; i < numbers.size(); i++)
    {
        auto numbers2 = split(numbers[i], "*");
        if (numbers2.size() > 1)    //There were * on the string
        {
            //Erase old string (that contained *)
            numbers.erase(numbers.begin() + i);
            for(int j = 0; j < numbers2.size(); j++)
            {
                numbers.insert(numbers.begin() + i + j, numbers2[j]);
            }

            for (int j = 0; j < numbers2.size() - 1; j++) //Add a * operand for each pair of multiplied numbers
            {
                operations.insert(operations.begin() + i, '*');
            }
        }
    }

    result = std::stoi(numbers[0]);
    for (int i = 1; i < numbers.size(); i++)
    {
        if (operations[(size_t)i - 1] == '+')
        {
            result += std::stoll(numbers[i]);
        }
        else if (operations[(size_t)i - 1] == '*')
        {
            result *= std::stoll(numbers[i]);
        }
    }

    return result;
}

long long Day18::solve2(std::string expression)
{
    long long result = 0;
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());

    std::vector<std::string> numbers;

    numbers = split(expression, "+");
    std::vector<char> operations(numbers.size() - 1, '+');  //number i and i+1 are related by the operation i

    for (int i = 0; i < numbers.size(); i++)
    {
        auto numbers2 = split(numbers[i], "*");
        if (numbers2.size() > 1)    //There were * on the string
        {
            //Erase old string (that contained *)
            numbers.erase(numbers.begin() + i);
            for (int j = 0; j < numbers2.size(); j++)
            {
                numbers.insert(numbers.begin() + i + j, numbers2[j]);
            }

            for (int j = 0; j < numbers2.size() - 1; j++) //Add a * operand for each pair of multiplied numbers
            {
                operations.insert(operations.begin() + i, '*');
            }
        }
    }

    std::vector<long long>numbersToMultiply;

    for (int i = 0; i < numbers.size() - 1; i++)
    {
        if (operations[i] == '*')
        {
            if (i == 0)
            {
                numbersToMultiply.push_back(std::stoll(numbers[i]));
            }
            else if (operations[(size_t)i - 1] == '*')
            {
                numbersToMultiply.push_back(std::stoll(numbers[i]));
            }
        }

        if (operations[(size_t)i] == '+')
        {
            int end = i;    //Last number of the sum
            while (end < operations.size() - 1 && operations[end + 1] == '+')
            {
                end++;
            }

            long long sum = 0;
            for (int j = i; j <= end + 1; j++)
            {
                sum += std::stoll(numbers[j]);
            }

            numbersToMultiply.push_back(sum);
            i = end;

        }
    }

    //Add last number
    if (operations[operations.size() - 1] == '*')
    {
        numbersToMultiply.push_back(std::stoll(numbers[numbers.size() - 1]));
    }

    result = 1;

    for (long long number : numbersToMultiply)
    {
        result *= number;
    }

    return result;
}