#pragma once
#include <vector>
#include <string>

static std::vector<std::string> stringSplit(const std::string& original, char separator)
{
	std::vector<std::string> results;
	std::string::const_iterator start = original.begin();
	std::string::const_iterator next = std::find(start, original.end(), separator);
	while (next != original.end())
	{
		results.push_back(std::string(start, next));
		start = next + 1;
		next = std::find(start, original.end(), separator);
	}
	results.push_back(std::string(start, next));
	return results;
}