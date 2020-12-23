#include "Day19.h"

std::string Day19::part1()
{
    auto input = loadFileAsStringList(pathToInput1);

    std::unordered_map<int, std::string> rules;

    std::unordered_map<int, int> lengths;   //Length (number of characters) of each rule

    int i = 0;
    while(i < input.size())
    {
        size_t colonPos = input[i].find_first_of(':');
        if (colonPos != std::string::npos)
        {
            int ruleNumber = std::stoi(input[i].substr(0, colonPos));
            rules[ruleNumber]= input[i].substr(colonPos + 2, input[i].size() - colonPos - 2);
        }
        else
        {
            i++;    //Skip empty line
            break;
        }

        i++;
    }

    for (auto& ruleNumber : rules)
    {
        calculateLengths(ruleNumber.first, rules, lengths);
    }



    int count = 0;
    while (i < input.size())
    {
        if (match(input[i], 0, rules, lengths))
        {
            count++;
        }
        i++;
    }

   


    return std::to_string(count);
}

std::string Day19::part2()
{
    auto input = loadFileAsStringList(pathToInput2);

    std::unordered_map<int, std::string> rules;

    std::unordered_map<int, int> lengths;   //Length (number of characters) of each rule

    int i = 0;
    while (i < input.size())
    {
        size_t colonPos = input[i].find_first_of(':');
        if (colonPos != std::string::npos)
        {
            int ruleNumber = std::stoi(input[i].substr(0, colonPos));
            rules[ruleNumber] = input[i].substr(colonPos + 2, input[i].size() - colonPos - 2);
        }
        else
        {
            i++;    //Skip empty line
            break;
        }

        i++;
    }

    for (auto& ruleNumber : rules)
    {
        calculateLengths(ruleNumber.first, rules, lengths);
    }



    int count = 0;
    while (i < input.size())
    {
        size_t startPos = 0;

        bool matched = true;

        size_t endPos = input[i].size() - 1;
        size_t startPos2 = 0;

        while (match(input[i].substr(startPos, lengths[8]), 8, rules, lengths))
        {
            startPos += lengths[8];
            endPos = input[i].size() - 1;
            startPos2 = startPos;
            matched = true;

            if ((endPos + 1) - startPos < (size_t)lengths[42] + lengths[31])
            {
                matched = false;
                break;
            }

            while ((endPos + 1) - startPos2 >= (size_t)lengths[42] + lengths[31] && matched)
            {

                if (match(input[i].substr(startPos2, lengths[42]), 42, rules, lengths)
                    && match(input[i].substr(endPos - lengths[31] + 1, lengths[31]), 31, rules, lengths))
                {
                    startPos2 += lengths[42];
                    endPos -= lengths[31];
                }
                else
                {
                    matched = false;
                    break;
                }
            }
            if (matched && startPos2 == endPos + 1)
            {
                break;
            }
        }
       
        if (matched && startPos2 == endPos + 1)
        {
            count++;
        }
        i++;
    }




    return std::to_string(count);
}

int Day19::calculateLengths(int ruleNumber, std::unordered_map<int, std::string>& rules, std::unordered_map<int, int>& lengths)
{
    if (lengths[ruleNumber] != 0)
    {
        return lengths[ruleNumber];
    }

    if (rules[ruleNumber].find_first_of('\"') != std::string::npos)
    {
        lengths[ruleNumber] = 1;
        return 1;
    }

    int length = 0;

    for (auto& number : split(split(rules[ruleNumber], "|")[0], " "))
    {
        length += calculateLengths(std::stoi(number), rules, lengths);
    }
    lengths[ruleNumber] = length;
    return length;
}

bool Day19::match(const std::string& line, int ruleNumber, std::unordered_map<int, std::string>& rules, std::unordered_map<int, int>& lengths)
{
    if (rules[ruleNumber].find_first_of('\"') != std::string::npos)
    {
        if (line.length() == 1 && line[0] == rules[ruleNumber][1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    for (auto& option : split(rules[ruleNumber], "|"))
    {
        size_t lastChar = 0;    //Last char of the previous pattern
        bool matches = true;
        for (auto& numberStr : split(option, " "))
        {
            int number = std::stoi(numberStr);
            if (!match(line.substr(lastChar, lengths[number]), number, rules, lengths))
            {
                matches = false;
                break;
            }
            lastChar += lengths[number];
        }

        if (matches && lastChar == line.size())
        {
            return true;
        }
    }
    return false;
}