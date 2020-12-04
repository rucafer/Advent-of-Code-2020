#include "Day4.h"

std::string Day4::part1()
{
	std::string input = loadFileAsString(pathToInput1);
	int validPassports = 0;

	for (auto& passport : split(input, "\n\n"))
	{
		std::vector<std::string> fields;

		for (auto& line : split(passport, "\n"))
		{
			for (auto& field : split(line, " "))
			{
				std::string fieldName = field.substr(0, field.find_first_of(":"));
				//Ignore cid field
				if (fieldName != "cid")
				{
					fields.push_back(fieldName);
				}
			}
		}

		//Fields count must be equal to the number of compulsory fields
		if (fields.size() != compulsoryFields.size())
		{
			continue;
		}

		bool containsAllFields = true;
		for (auto& compField : compulsoryFields)
		{
			if (std::find(fields.begin(), fields.end(), compField) == fields.end())
			{
				containsAllFields = false;
				break;
			}
		}

		if (containsAllFields)
		{
			validPassports++;
		}
	}

	return std::to_string(validPassports);
}

std::string Day4::part2()
{
	std::string input = loadFileAsString(pathToInput1);
	int validPassports = 0;

	for (auto& passport : split(input, "\n\n"))
	{
		std::vector<std::string> fields;

		bool hasInvalidFields = false;

		for (auto& line : split(passport, "\n"))
		{
			for (auto& field : split(line, " "))
			{
				if (field.substr(0, field.find_first_of(":")) != "cid")
				{
					fields.push_back(field);
				}
			}
		}

		for (auto& field : fields)
		{
			if (!isFieldValid(field))
			{
				hasInvalidFields = true;
				break;
			}
		}

		//Check that there aren't any repeated fields

		//Fields count must be equal to the number of compulsory fields
		if (fields.size() != compulsoryFields.size())
		{
			continue;
		}

		bool containsAllFields = true;
		for (std::string compField : compulsoryFields)
		{
			bool found = false;
			for(auto& field : fields){
				if (field.substr(0, field.find_first_of(":")) == compField)
				{
					found = true;
				}
			}

			if (!found)
			{
				containsAllFields = false;
				break;
			}
		}

		if (containsAllFields && !hasInvalidFields)
		{
			validPassports++;
		}
	}

	return std::to_string(validPassports);
}

bool Day4::isFieldValid(const std::string& field)
{

	size_t colonPos = field.find_first_of(":");
	std::string fieldName = field.substr(0, colonPos);
	std::string value = field.substr(colonPos + 1, field.size() - colonPos - 1);

	if (fieldName == "byr")
	{
		int year = std::stoi(value);
		if (year < 1920 || year > 2002)
		{
			return false;
		}
	}
	else if (fieldName == "iyr")
	{
		int year = std::stoi(value);
		if (year < 2010 || year > 2020)
		{
			return false;
		}
	}
	else if (fieldName == "eyr")
	{
		int year = std::stoi(value);
		if (year < 2020 || year > 2030)
		{
			return false;
		}
	}
	else if (fieldName == "hgt")
	{
		if (value.size() < 4)
		{
			return false;
		}
		else
		{
			int height = std::stoi(value.substr(0, value.size() - 2));
			std::string unit = value.substr(value.size() - 2, 2);
			if (unit == "cm")
			{
				if (height < 150 || height > 193)
				{
					return false;
				}
			}
			else if (unit == "in")
			{
				if (height < 59 || height > 76)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else if (fieldName == "hcl")
	{
		if (value[0] != '#')
		{
			return false;
		}

		for (char c : value.substr(1, value.size() - 1))
		{
			if (!(c >= 48 && c <= 57) &&	//numbers
				!(c >= 97 && c <= 102))	//a-f
			{
				return false;
			}
		}
	}
	else if (fieldName == "ecl")
	{
		if (value != "amb" && value != "blu" && value != "brn" && value != "gry" &&
			value != "grn" && value != "hzl" && value != "oth")
		{
			return false;
		}
	}
	else if (fieldName == "pid")
	{
		if (value.size() != 9)
		{
			return false;
		}

		for (char c : value)
		{
			if (c < 48 || c > 57)
			{
				return false;	//Not a number
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

