#include <iostream>
#include <fstream>
#include <sstream>

#include "main.h"
#include "utils.h"

int main()
{
	std::fstream schedulesFile("schedules.txt", std::ios::in);

	std::stringstream ssBuffer;
	ssBuffer << schedulesFile.rdbuf();
	auto schedulesSTR = ssBuffer.str();
	std::cout << "Schedules from file:\n" << schedulesSTR << "\n";
	std::vector<Task> pool;
	try
	{
		parseInputSTR(schedulesSTR, pool);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error while parsing:\n" << ex.what() << "\nClosing";
	}
	try
	{
		validateTasks(pool);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error while executing:\n" << ex.what() << "\nClosing";
	}
}

void parseInputSTR(const std::string& schedulesSTR, std::vector<Task>& pool)
{
	auto tasksSTR = stringSplit(schedulesSTR, '\n');
	for (auto& taskSTR : tasksSTR)
	{
		auto prerequisites = stringSplit(taskSTR, ' ');
		if (prerequisites.size() > 0)
		{
			prerequisites[0].erase(prerequisites[0].end() - 1, prerequisites[0].end());//remove ':' from task name
			//looking for self dependency
			if (std::find(prerequisites.begin() + 1, prerequisites.end(), prerequisites[0]) == prerequisites.end())
			{
				Task tmpTask;
				tmpTask.name = prerequisites[0];
				prerequisites.erase(prerequisites.begin());//removes task itself from input
				tmpTask.prerequisites = prerequisites;
				pool.push_back(tmpTask);
			}
			else
			{
				throw std::exception("self depended task founded");
			}
		}
	}
}

void validateTasks(const std::vector<Task>& pool)
{
	std::vector<Task> noPrerequisitesCount;
	for (auto& task : pool)
	{
		if (task.prerequisites.size() == 0)
		{
			noPrerequisitesCount.push_back(task);
		}
	}
	if (noPrerequisitesCount.size() > 1)
	{
		//TODO show what root tasks are founded
		throw std::exception("multiple branches detected");
	}
	if (noPrerequisitesCount.size() == 0)
	{
		throw std::exception("cyclic dependency detected, no root task founded");
	}

	int stepsNeeded = 0;
	while (true)
	{
		break;
	}
	std::cout << "Given tasks can be executed in: " << stepsNeeded << " steps\n";
}
