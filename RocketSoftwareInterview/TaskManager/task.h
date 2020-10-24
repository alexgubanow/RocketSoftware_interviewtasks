#pragma once
#include <string>
#include <vector>

struct Task
{
	std::string name;
	std::vector<std::string> prerequisites;
};

