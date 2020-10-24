#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"

class Task
{
public:
	std::string name;
	std::vector<std::string> prerequisites;
	static void parseInputSTR(const std::string& schedulesSTR, std::vector<Task>& pool)
	{
		auto tasksSTR = stringSplit(schedulesSTR, '\n');
		for (auto& taskSTR : tasksSTR)
		{
			auto prerequisites = stringSplit(taskSTR, ' ');
			if (prerequisites.size() > 0)
			{
				//remove ':' from task name
				prerequisites[0].erase(prerequisites[0].end() - 1, prerequisites[0].end());
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

	static void validateTasks(const std::vector<Task>& pool, std::string& rootTaskName)
	{
		std::vector<Task> rootTasks;
		for (auto& task : pool)
		{
			if (task.prerequisites.size() == 0)
			{
				rootTasks.push_back(task);
			}
		}
		if (rootTasks.size() > 1)
		{
			std::ostringstream errStream;
			errStream << "multiple branches detected, list of founded tasks:\n";
			for (auto& task : rootTasks)
			{
				errStream << task.name << '\n';
			}
			throw std::exception(errStream.str().c_str());
		}
		if (rootTasks.size() == 0)
		{
			throw std::exception("no root task founded, probably exist cyclic dependency");
		}
		for (auto& task : pool)
		{
			for (auto& prerequisite : task.prerequisites)
			{
				if (std::count_if(pool.begin(), pool.end(), [prerequisite](Task t) { return t.name == prerequisite; }) == 0)
				{
					std::ostringstream errStream;
					errStream << "unresolvable dependencies found, task name:\n" << prerequisite;
					throw std::exception(errStream.str().c_str());
				}
			}
		}
		rootTaskName = rootTasks[0].name;
	}

	static int countStepsNeeded(const std::vector<Task>& pool, const std::string& rootTaskName)
	{
		size_t stepsNeeded = 1;
		std::vector<std::string> currStepTasks{ rootTaskName };
		while (stepsNeeded < pool.size())
		{
			std::vector<std::string> nextStepTasks;
			for (auto& task : pool)
			{
				for (auto& currStepTask : currStepTasks)
				{
					if (std::find(task.prerequisites.begin(), task.prerequisites.end(), currStepTask) != task.prerequisites.end())
					{
						nextStepTasks.push_back(task.name);
					}
				}
			}
			if (nextStepTasks.size() == 0)
			{
				break;
			}
			stepsNeeded++;
			currStepTasks = nextStepTasks;
		}
		if (stepsNeeded == 1 && pool.size() > 1)
		{
			throw std::exception("multiple branches detected");
		}
		return stepsNeeded;
	}
};
