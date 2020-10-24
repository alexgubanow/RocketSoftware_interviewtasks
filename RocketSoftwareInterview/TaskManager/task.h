#pragma once
#include <string>
#include <vector>
class Task
{
private:

public:
	std::string _name;
	std::vector<std::string> _prerequisites;
	Task(const std::string& name):_name(name) {};
	void run();
};

